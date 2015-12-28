//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/real_time_client.h"
#include "slack/websocket.h"
#include "private.h"
#include <json/json.h>
#include <thread>

#include <iostream>

namespace slack
{

namespace event
{
void initialize_events(void); //declared in event.cpp
}

// This method will block until the connection is complete

void real_time_client::initialize_()
{
    event::initialize_events();

    if (!websocket_)
    {
        websocket_ = std::make_shared<slack::simple_websocket>();
    }
    websocket_->on_connect = std::bind(&real_time_client::on_connect_, this);
    websocket_->on_close = std::bind(&real_time_client::on_close_, this, std::placeholders::_1);
    websocket_->on_error = std::bind(&real_time_client::on_error_, this, std::placeholders::_1);
    websocket_->on_message = std::bind(&real_time_client::on_message_, this, std::placeholders::_1);
}


real_time_client::~real_time_client()
{
    std::cout << "D'TOR" << std::endl;

    stop();
}

void real_time_client::start()
{
    if(auto_reconnect_)
    {
        //connect...
        websocket_->start(url_);

        //Uh-oh, if we got here, we lost the connection somehow. Let's see if we ought to reconnect
        while(!is_connected_ and should_reconnect_ and (reconnect_count_ <= reconnect_policy_.max_reconnect_attempts) )
        {
            std::unique_lock<std::mutex> lk{reconnect_cv_mutex_};
            if (ping_cv_.wait_for(lk, next_reconnect_interval_, [this] {
                return !!(this->is_connected_);
            }))
            {
                //is_connected has changed to true
                std::cout << "No reconnect! " << std::endl;
                //basically no-op here, fall through, and let the while loop terminate to start the reconnect process
            }
            else
            {
                //timed out---let's try to reconnect
                std::cout << "Ping! " << std::endl;
                websocket_->start(url_);
            }
            lk.unlock();
        }
    }
    else //no auto reconect
    {
        websocket_->start(url_);
    }

    reset_reconnect_(); //reset the connection policy for the next connection request
}

void real_time_client::stop()
{
    should_reconnect_ = false;
    do_stop_();
}

void real_time_client::on_connect_()
{
    is_connected_ = true; //it's atomic, so this is ok!
    std::cout << "Connect!" << std::endl;

    reset_reconnect_(); //reset the reconnect interval to the default

    // Start the ping thread
    if (auto_ping_)
    {
        ping_thread_ = std::thread{std::bind(&real_time_client::ping_worker_, this)};
    }

    if(on_connect)
    {
        on_connect();
    }
}


void real_time_client::on_close_(websocket::close_reason reason)
{
    std::cout << "Close!" << std::endl;
    do_stop_();

    //if *WE* didn't close the connection, try again
    //TODO might be other reasons NOT to reconnect
    if (auto_reconnect_ && (reason != websocket::close_reason::CLOSED_BY_CLIENT))
    {
        setup_reconnect_();
    }

    if(on_close)
    {
        on_close(reason, should_reconnect_);
    }
}



void real_time_client::on_error_(websocket::error_code error)
{
    std::cout << "Error!" << std::endl;
    do_stop_();

    //TODO, depending on the nature of the error, we should try reconnecting...or not.
    // E.g., we shouldn't reconnect on a bad hostname?
    if(auto_reconnect_) //todo what other reasons should we consider?
    {
        setup_reconnect_();
    }

    //and notify;
    if(on_error)
    {
        on_error(error, should_reconnect_);
    }
}


void real_time_client::on_message_(const std::string &message)
{
    //TODO this is where the rubber meets the road
    std::cout << "Message! " << message << std::endl;

    Json::Value result_ob;
    Json::Reader reader;
    bool parsed_success = reader.parse(message, result_ob, false);
    if (!parsed_success)
    {
        //TODO
        return;
    }

    std::string type = result_ob["type"].asString();
    auto event = slack_private::events_factory.create(type, result_ob);

    handle_event(event);

    if(on_message)
    {
        on_message(message);
    }
}


//TODO unsure about this logic. What is the right way to think about testing this?
void real_time_client::setup_reconnect_()
{
    should_reconnect_ = false;
    ++reconnect_count_;
    if(reconnect_count_ <= reconnect_policy_.max_reconnect_attempts)
    {
        should_reconnect_ = true;
        next_reconnect_interval_ *= reconnect_policy_.retry_backoff_factor;
    }
    reconnect_cv_.notify_one();
}

//TODO unsure about this logic. What is the right way to think about testing this?
void real_time_client::reset_reconnect_()
{
    should_reconnect_ = true;
    reconnect_count_ = 0;
    next_reconnect_interval_ = reconnect_policy_.retry_interval;
    reconnect_cv_.notify_one();
}

void real_time_client::ping_worker_()
{
    //send an initial ping
    websocket_->send_message("{\"id\": 0, \"type\": \"ping\"}");

    while (is_connected_)
    {
        std::unique_lock<std::mutex> lk{ping_cv_mutex_};
        if (ping_cv_.wait_for(lk, ping_interval_, [this] {
            return !(this->is_connected_);
        }))
        {
            //is_connected has changed to true
            std::cout << "No ping! " << std::endl;
            //basically no-op here, fall through, and let the while loop terminate
        }
        else
        {
            //timed out---this is the normal case, this is where we do the periodic work
            std::cout << "Ping! " << std::endl;
            websocket_->send_message("{\"id\": 1234, \"type\": \"ping\"}");
        }
        lk.unlock();
    }
    std::cout << "Ping thread stopping" << std::endl;
}


void real_time_client::do_stop_()
{
    websocket_->stop();

    is_connected_ = false; //just jumpstart that
    ping_cv_.notify_all(); //they're waiting on it!
    std::cout << "Disconnecting" << std::endl;

    if (ping_thread_.joinable())
    {
        ping_thread_.join();
    }
}

} //namespace slack