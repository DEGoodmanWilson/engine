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
//TODO
#include <Simple-WebSocket-Server/client_wss.hpp>

// We need to think very carefully about the threading model. Who owns the thread?

namespace slack
{
using WssClient = SimpleWeb::SocketClient<SimpleWeb::WSS>;
using event_handler = std::function<void(std::shared_ptr<base::event>)>;

class real_time_client
{
public:
//    real_time_client(); //do this later

    real_time_client(const std::string &url);

    void start();

    void stop();

    //TODO use something more sophisticated here?
    void register_event_handler(const std::string &type, event_handler handler);

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
    std::thread ping_thread_;
    std::map<std::string, event_handler> handlers_;

    void initialize_(void);
};

}