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
#include <mutex>
#include "websocket.h"

// We need to think very carefully about the threading model. Who owns the thread?

namespace slack
{

class real_time_client :
        public event::event_handler
{
public:
    //public interface
    template<typename ...Os>
    real_time_client(const std::string &url)
            :
            url_{url},
            auto_ping_{true},
            auto_reconnect_{true},
            websocket_{nullptr},
            is_connected_{false},
            ping_interval_{30000},
            reconnect_policy_{},
            next_reconnect_{reconnect_policy_.retry_interval_}
    {
        initialize_();
    }

    template<typename ...Os>
    real_time_client(const std::string &url, Os &&...os)
            :
            url_{url},
            auto_ping_{true},
            auto_reconnect_{true},
            websocket_{nullptr},
            is_connected_{false},
            ping_interval_{30000},
            reconnect_policy_{},
            next_reconnect_{reconnect_policy_.retry_interval_}
    {
        slack::set_option<real_time_client>(*this, std::forward<Os>(os)...);
        initialize_();
    }

    ~real_time_client();

    //parameters and setters
    //parameters
    struct parameter
    {
        MAKE_BOOL_LIKE(auto_ping);

        MAKE_BOOL_LIKE(auto_reconnect);

        MAKE_LONG_LONG_LIKE(ping_interval);

        using websocket = std::shared_ptr<websocket>;

        struct reconnect_policy
        {
            reconnect_policy() : retry_interval_{5000}, retry_backoff_factor_{2.0}
            { } //default backoff policy
            std::chrono::milliseconds retry_interval_;
            double retry_backoff_factor_;
        };
    };

    void set_option(parameter::auto_ping &auto_ping)
    { auto_ping_ = static_cast<bool>(auto_ping); }

    void set_option(parameter::auto_ping &&auto_ping)
    { auto_ping_ = static_cast<bool>(auto_ping); }

    void set_option(parameter::auto_reconnect &auto_reconnect)
    { auto_reconnect_ = static_cast<bool>(auto_reconnect); }

    void set_option(parameter::auto_reconnect &&auto_reconnect)
    { auto_reconnect_ = static_cast<bool>(auto_reconnect); }

    void set_option(parameter::ping_interval &ping_interval)
    { ping_interval_ = std::chrono::milliseconds{static_cast<long long>(ping_interval)}; }

    void set_option(parameter::ping_interval &&ping_interval)
    { ping_interval_ = std::chrono::milliseconds{static_cast<long long>(ping_interval)}; }

    void set_option(parameter::websocket &websocket)
    { websocket_ = websocket; }

    void set_option(parameter::websocket &&websocket)
    { websocket_ = std::move(websocket); }

    void set_option(parameter::reconnect_policy &reconnect_policy)
    {
        reconnect_policy_ = reconnect_policy;
        next_reconnect_ = reconnect_policy_.retry_interval_;
    }

    void set_option(parameter::reconnect_policy &&reconnect_policy)
    {
        reconnect_policy_ = std::move(reconnect_policy);
        next_reconnect_ = reconnect_policy_.retry_interval_;
    }

    // Clients can hook up to these for notification of websocket events
    std::function<void(void)> on_connect;
    std::function<void(const std::string &)> on_message;
    std::function<void(websocket::error_code)> on_error;
    std::function<void(websocket::close_reason)> on_close;

    void start();

    void stop();

    void set_ping_timeout(std::chrono::milliseconds timeout);

    //Method to send a message to Slack
//    void send_message(const slack::event::message& message);

private:
    void initialize_();

    void on_connect_();

    void on_close_(websocket::close_reason reason);

    void on_error_(websocket::error_code error);

    void on_message_(const std::string &message);

    std::string url_;

    bool auto_ping_;
    bool auto_reconnect_;
    std::shared_ptr<websocket> websocket_;
    std::chrono::milliseconds ping_interval_;
    parameter::reconnect_policy reconnect_policy_;
    std::chrono::milliseconds next_reconnect_;

    std::atomic<bool> is_connected_; //it's already atomic

    void ping_worker_();

    std::mutex ping_mutex_;
    std::condition_variable ping_cv_;
    std::thread ping_thread_;

};

}