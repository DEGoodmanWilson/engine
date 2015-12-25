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
real_time_client::real_time_client(std::shared_ptr<websocket> socket)
        : socket_{std::move(socket)}, is_connected_{false}, ping_timeout_{30000}
{
    event::initialize_events();

    socket_->on_connect = std::bind(&real_time_client::on_connect_, this);
    socket_->on_close = std::bind(&real_time_client::on_close_, this, std::placeholders::_1);
    socket_->on_error = std::bind(&real_time_client::on_error_, this, std::placeholders::_1);
    socket_->on_message = std::bind(&real_time_client::on_message_, this, std::placeholders::_1);
}


real_time_client::~real_time_client()
{
    std::cout << "D'TOR" << std::endl;

    stop();
}

void real_time_client::start()
{
    socket_->start();
}


void real_time_client::stop()
{
    std::unique_lock<std::mutex> lk{ping_mutex_};

    socket_->stop();

    is_connected_ = false; //just jumpstart that
    ping_cv_.notify_all(); //they're waiting on it!
    std::cout << "Disconnecting" << std::endl;

    lk.unlock();

    if (ping_thread_.joinable())
    {
        ping_thread_.join();
    }
}


void real_time_client::set_ping_timeout(std::chrono::milliseconds timeout)
{
    ping_timeout_ = timeout;
}

void real_time_client::on_connect_()
{
    is_connected_ = true; //it's atomic, so this is ok!
    std::cout << "Connect!" << std::endl;

    // Start the ping thread
    ping_thread_ = std::thread{std::bind(&real_time_client::ping_worker_, this)};
}


void real_time_client::on_close_(websocket::close_reason reason)
{
    std::cout << "Close!" << std::endl;
    stop();
}


void real_time_client::ping_worker_()
{
    //send an initial ping
    socket_->send_message("{\"id\": 0, \"type\": \"ping\"}");

    while (is_connected_)
    {
        std::unique_lock<std::mutex> lk{ping_mutex_};
        ping_cv_.wait_for(lk, ping_timeout_, [this] {
            std::cout << "wait_for " << this->is_connected_ << std::endl;
            return !(this->is_connected_);
        });

        if(this->is_connected_)
        {
            std::cout << "Ping! " << std::endl;
            socket_->send_message("{\"id\": 1234, \"type\": \"ping\"}");
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
}

} //namespace slack