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
    websocket_->start(url_);
}

//void real_time_client::restart_()
//{
//    next_reconnect_ *= * reconnect_policy_.retry_backoff_factor_;
//    //TODO start a timer going, because we won't get a disconnect message if we fail to connect.
//    real_time_client->start();
//}


void real_time_client::stop()
{
    std::unique_lock<std::mutex> lk{ping_mutex_};

    websocket_->stop();

    is_connected_ = false; //just jumpstart that
    ping_cv_.notify_all(); //they're waiting on it!
    std::cout << "Disconnecting" << std::endl;

    lk.unlock();

    if (ping_thread_.joinable())
    {
        ping_thread_.join();
    }
}

void real_time_client::on_connect_()
{
    is_connected_ = true; //it's atomic, so this is ok!
    std::cout << "Connect!" << std::endl;

    next_reconnect_ = reconnect_policy_.retry_interval_; //reset the reconnect interval to the default

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
    //if we didn't close, try again
    if (auto_reconnect_ && (reason != websocket::close_reason::CLOSED_BY_CLIENT))
    {
        //reconnect
//        std::cout << "Will try reconnect in " << next_reconnect_ << " milliseconds" << std::endl;
        return;
    }

    std::cout << "Close!" << std::endl;
    stop();

    if(on_close)
    {
        on_close(reason);
    }
}


void real_time_client::ping_worker_()
{
    //send an initial ping
    websocket_->send_message("{\"id\": 0, \"type\": \"ping\"}");

    while (is_connected_)
    {
        std::unique_lock<std::mutex> lk{ping_mutex_};
        ping_cv_.wait_for(lk, ping_interval_, [this] {
            std::cout << "wait_for " << this->is_connected_ << std::endl;
            return !(this->is_connected_);
        });

        if (this->is_connected_)
        {
            std::cout << "Ping! " << std::endl;
            websocket_->send_message("{\"id\": 1234, \"type\": \"ping\"}");
        }
        else
        {
            std::cout << "No ping! " << std::endl;
        }
        lk.unlock();
    }
    std::cout << "Ping thread stopping" << std::endl;
}

void real_time_client::on_error_(websocket::error_code error)
{
    std::cout << "Error!" << std::endl;
    //TODO

    if(on_error)
    {
        on_error(error);
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

} //namespace slack