//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <string>
#include <memory>
#include <functional>

//TODO
#include <slack/types.h>
#include <thread>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

// We need to think very carefully about the threading model. Who owns the thread?

namespace slack
{

//namespace impl
//{
//    class real_time_client;
//}

enum class real_time_message_types
{
    message,
    foo,
    bar,
};

class real_time_client
{
public:
//    real_time_client(); //do this later

    real_time_client(const std::string& url);
    ~real_time_client();

    //TODO this method will block while the connection is being made.
    bool run();

    //TODO use something more sophisticated here?
    void register_callback(real_time_message_types type, std::function<void(const message&)>> handler);

private:
    websocketpp::client<websocketpp::config::asio_client> client_;
    websocketpp::connection_hdl hdl_;
    websocketpp::lib::mutex lock_;
    bool open_;
    bool done_;
    std::string& url_;
    websocketpp::lib::thread asio_thread_;
    websocketpp::lib::thread telemetry_thread_
};

}