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
//TODO The way to do this is to factor out the websocket here, and use an abstract interface that
// the user can optionally provide, just as we do with CPR

#include <Simple-WebSocket-Server/client_wss.hpp>

// We need to think very carefully about the threading model. Who owns the thread?

namespace slack
{
using WssClient = SimpleWeb::SocketClient<SimpleWeb::WSS>;

class real_time_client : public event::event_handler
{
public:
    using on_open_callback_t = std::function<void()>;
    using on_close_callback_t = std::function<void()>;
    using on_error_callback_t = std::function<void()>;

    real_time_client(const std::string &url);

    //TODO should we just make these fields public and assignable?
    real_time_client(const std::string &url,
                     on_open_callback_t on_open_callback,
                     on_close_callback_t on_close_callback,
                     on_error_callback_t on_error_callback
    );


    void start();

    void stop();

    //these can be used in case we don't want to use our own websocket implementation

    void handle_event_from_slack(const std::string& event_str);

    bool post_event_to_slack(std::shared_ptr<base::event> event);

protected:
    friend class SimpleWeb::SocketClient<SimpleWeb::WSS>;

    void on_open_();

    void on_close_(int status, const std::string &reason);

    void on_error_(const boost::system::error_code &error_code);

    void on_message_(std::shared_ptr<WssClient::Message> message);

private:
    WssClient wss_client_;
    std::atomic<bool> is_connected_;

    on_open_callback_t on_open_callback_;
    on_close_callback_t on_close_callback_;
    on_error_callback_t on_error_callback_;

    std::thread ping_thread_;

    void initialize_(void);
};

}