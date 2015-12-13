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
#include <Simple-WebSocket-Server/client_wss.hpp>

// We need to think very carefully about the threading model. Who owns the thread?

namespace slack
{
using WssClient = SimpleWeb::SocketClient<SimpleWeb::WSS>;

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

    void start();

    void stop();

    //TODO use something more sophisticated here?
//    void register_callback(real_time_message_types type, std::function<void(const message&)>> handler);

protected:
    friend class SimpleWeb::SocketClient<SimpleWeb::WSS>;
    void on_open_();
    void on_close_(int status, const std::string& reason);
    void on_error_(const boost::system::error_code&error_code);
    void on_message_(std::shared_ptr<WssClient::Message> message);

private:
    WssClient wss_client_;
    std::atomic<bool> is_connected_;
    std::thread ping_thread_;
};

}