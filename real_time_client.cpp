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
    stop();
}

void real_time_client::start()
{
    socket_->start();
}


void real_time_client::start_async()
{
    if(is_socket_thread_running) return;

    socket_thread_ = std::thread{[this]() {
        is_socket_thread_running = true;
        socket_->start();
    }};
}

void real_time_client::stop()
{
    //TODO stop ping!

    socket_->stop();

    if (is_socket_thread_running && socket_thread_.joinable())
    {
        std::lock_guard<std::mutex> lock{socket_mutex_};

        is_socket_thread_running = false;

        socket_thread_.join();
    }

}

void real_time_client::on_connect_()
{
    is_connected_ = true; //it's atomic, so this is ok!
    // TODO And start the ping thread
}


void real_time_client::on_close_(websocket::close_reason reason)
{
    is_connected_ = false;
    //TODO other things.
    // and stop the ping thread
}


void real_time_client::on_error_(websocket::error_code error)
{
    //TODO
}


void real_time_client::on_message_(const std::string &message)
{
    //TODO this is where the rubber meets the road

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