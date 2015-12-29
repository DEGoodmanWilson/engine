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
    real_time_client()
            :
            url_{},
            auto_ping_{true},
            auto_reconnect_{true},
            websocket_{nullptr},
            is_connected_{false},
            ping_interval_{30000},
            reconnect_policy_{}
    {
        initialize_();
    }

    template<typename ...Os>
    real_time_client(Os &&...os)
            :
            url_{},
            auto_ping_{true},
            auto_reconnect_{true},
            websocket_{nullptr},
            is_connected_{false},
            ping_interval_{30000},
            reconnect_policy_{}
    {
        slack::set_option<real_time_client>(*this, std::forward<Os>(os)...);
        initialize_();
    }

    ~real_time_client();

    //parameters and setters
    //parameters
    struct parameter
    {
        MAKE_STRING_LIKE(url);

        MAKE_BOOL_LIKE(auto_ping);

        MAKE_BOOL_LIKE(auto_reconnect);

        MAKE_LONG_LONG_LIKE(ping_interval);

        using websocket = std::shared_ptr<websocket>;

        struct reconnect_policy
        {
            reconnect_policy() : max_reconnect_attempts{10}, retry_interval{5000}, retry_backoff_factor{2.0}
            { } //default backoff policy

            reconnect_policy(uint16_t max_reconnect_attempts,
                             std::chrono::milliseconds retry_interval,
                             double retry_backoff_factor) :
                    max_reconnect_attempts{max_reconnect_attempts},
                    retry_interval{retry_interval},
                    retry_backoff_factor{retry_backoff_factor}
            { }

            uint16_t max_reconnect_attempts;
            std::chrono::milliseconds retry_interval;
            double retry_backoff_factor;
        };
    };

    void set_option(parameter::url &url)
    { url_ = url; }

    void set_option(parameter::url &&url)
    { url_ = std::move(url); }

    void set_option(parameter::auto_ping &auto_ping)
    { auto_ping_ = static_cast<bool>(auto_ping); }

    void set_option(parameter::auto_ping &&auto_ping)
    { auto_ping_ = static_cast<bool>(auto_ping); }

    void set_option(parameter::auto_reconnect &auto_reconnect)
    {
        auto_reconnect_ = static_cast<bool>(auto_reconnect);
        should_reconnect_ = auto_reconnect_;
    }

    void set_option(parameter::auto_reconnect &&auto_reconnect)
    {
        auto_reconnect_ = static_cast<bool>(auto_reconnect);
        should_reconnect_ = auto_reconnect_;
    }

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
        next_reconnect_interval_ = reconnect_policy_.retry_interval;
    }

    void set_option(parameter::reconnect_policy &&reconnect_policy)
    {
        reconnect_policy_ = std::move(reconnect_policy);
        next_reconnect_interval_ = reconnect_policy_.retry_interval;
    }

    // Clients can hook up to these for notification of websocket events
    std::function<void(void)> on_connect;
    std::function<void(const std::string &)> on_message;
    std::function<void(websocket::error_code, bool will_try_reconnect)> on_error;
    std::function<void(websocket::close_reason, bool will_try_reconnect)> on_close;

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

    std::atomic<bool> is_connected_; //it's already atomic

    void ping_worker_();

    std::mutex ping_cv_mutex_;
    std::condition_variable ping_cv_;
    std::thread ping_thread_;

    bool should_reconnect_; //there is no multi-threading involved here, no need for atomics.
    uint16_t reconnect_count_;
    std::chrono::milliseconds next_reconnect_interval_;
    std::mutex reconnect_cv_mutex_;
    std::condition_variable reconnect_cv_;

    void setup_reconnect_();

    void reset_reconnect_();

    void do_stop_();

};

}