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
        : socket_{std::move(socket)}, is_connected_{false}, is_socket_thread_running{false}
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


void real_time_client::start_async()
{
    if (is_socket_thread_running) return;

    socket_thread_ = std::thread{[this]() {
        is_socket_thread_running = true;
        socket_->start();
        is_socket_thread_running = false;
    }};
}

void real_time_client::stop()
{
    socket_->stop();

    is_connected_ = false; //just jumpstart that
    ping_cv_.notify_all(); //they're waiting on it!
    std::cout << "Disconnecting" << std::endl;

    if (socket_thread_.joinable())
    {
        socket_thread_.join();
    }

    if (ping_thread_.joinable())
    {
        ping_thread_.join();
    }
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
    is_connected_ = false; //this _shoud_ stop the ping thread
    ping_cv_.notify_all(); //they're waiting on it!
    std::cout << "Close!" << std::endl;
    //TODO other things. This function is a bit messed up. Should we call stop?
}


void real_time_client::ping_worker_()
{
    //send an initial ping
    socket_->send_message("{\"id\": 0, \"type\": \"ping\"}");

    while (is_connected_)
    {
        std::unique_lock<std::mutex> lk{ping_mutex_};
        ping_cv_.wait_for(lk, std::chrono::milliseconds(30000), [this] {
            std::cout << "wait_for" << std::endl;
            return !(this->is_connected_);
        });

        std::cout << "Ping! " << std::endl;

        //TODO be better about how this is done.
        socket_->send_message("{\"id\": 1234, \"type\": \"ping\"}");

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