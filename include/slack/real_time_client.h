//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/event.h>
#include <slack/base/event.h>
#include <string>
#include <memory>
#include <functional>
#include <thread>
#include "websocket.h"

// We need to think very carefully about the threading model. Who owns the thread?

namespace slack
{

class real_time_client : public event::event_handler
{
public:
    real_time_client(std::shared_ptr<websocket> socket);
    ~real_time_client();

    void start();
    void start_async();
    void stop();

    //Method to send a message to Slack
//    void send_message(const slack::event::message& message);

private:
    void on_connect_();

    void on_close_(websocket::close_reason reason);

    void on_error_(websocket::error_code error);

    void on_message_(const std::string &message);


    std::shared_ptr<websocket> socket_;

    std::atomic<bool> is_connected_;

    std::thread socket_thread_;
    std::thread ping_thread_;
};

}