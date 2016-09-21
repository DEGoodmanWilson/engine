//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/event/events.h>
#include <slack/types.h>
#include <slack/safe_queue.h>
#include <typeindex>
#include <string>
#include <vector>
#include <regex>
#include <utility>
#include <atomic>


namespace slack
{

struct http_event_envelope
{
    slack::verification_token verification_token;
    struct token token;
    std::string api_app_id;
    std::vector<user_id> authed_users;
};

class http_event_handler_callback
{
public:
    virtual ~http_event_handler_callback() = default;

    void exec(std::shared_ptr<slack::base::event> event, const http_event_envelope& envelope)
    {
        call(event, envelope);
    }

private:
    virtual void call(std::shared_ptr<slack::base::event>, const http_event_envelope&) = 0;
};


template<class EventT>
class http_event_handler_callback_template :
        public http_event_handler_callback
{
public:
    http_event_handler_callback_template(std::function<void(std::shared_ptr<EventT>, const http_event_envelope& envelope)> memFn) : function_(memFn)
    {};

    void call(std::shared_ptr<slack::base::event> event, const http_event_envelope& envelope)
    {
        function_(std::static_pointer_cast<EventT>(event), envelope);
    }

private:
    std::function<void(std::shared_ptr<EventT>, const http_event_envelope& envelope)> function_;
};

class http_event_client
{
public:

    struct parameter
    {
        using thread_timeout = std::chrono::milliseconds;

        using thread_count = long;
    };

    template<class VERIFICATION_TOKEN, typename ...Os>
    http_event_client(VERIFICATION_TOKEN &&verification_token) :
            verification_token_{std::forward<VERIFICATION_TOKEN>(verification_token)}, thread_timeout_{500ms}, thread_count_{1}, running_{ATOMIC_FLAG_INIT}
    {
        initialize_();
    }

    template<class VERIFICATION_TOKEN, typename ...Os>
    http_event_client(VERIFICATION_TOKEN &&verification_token, Os &&...os) :
            verification_token_{std::forward<VERIFICATION_TOKEN>(verification_token)}, thread_timeout_{500ms}, thread_count_{1}, running_{ATOMIC_FLAG_INIT}
    {
        slack::set_option<http_event_client>(*this, std::forward<Os>(os)...);
        initialize_();
    }

    virtual ~http_event_client();

    void set_option(const parameter::thread_timeout &thread_timeout)
    { thread_timeout_ = thread_timeout; }
    void set_option(parameter::thread_timeout &&thread_timeout)
    { thread_timeout_ = std::move(thread_timeout); }

    void set_option(const parameter::thread_count &thread_count)
    { thread_count_ = thread_count; }
    void set_option(parameter::thread_count &&thread_count)
    { thread_count_ = std::move(thread_count); }


    virtual std::string handle_event(const std::string &event, const token &token);

    // event handlers
    template<class EventT>
    void on(std::function<void(std::shared_ptr<EventT>, const http_event_envelope &envelope)> handler);
    template<class EventT>
    void remove_on();
    void on_error(std::function<void(std::string message, std::string received)> handler);
    void remove_on_error();

    // message handlers
    struct message
    {
        std::string text;
        user_id from_user_id;
        struct channel_id channel_id;
        struct token token;

        void reply(std::string text) const;
    };
    using hears_cb = std::function<void(const struct message &message)>;
    template<typename T>
    void hears(T &&message, hears_cb callback)
    {
        callbacks_.emplace_back(std::regex{std::forward<T>(message)}, callback);
    }

private:
    verification_token verification_token_;
    parameter::thread_timeout thread_timeout_;
    parameter::thread_count thread_count_;

    using handler_map = std::map<std::type_index, std::unique_ptr<http_event_handler_callback>>;
    handler_map handlers_;
    std::function<void(std::string message, std::string received)> error_handler_;
    //let's just brute force this for now
    std::vector<std::pair<std::regex, hears_cb>> callbacks_;

    //background processing of event safe_queue
    std::vector<std::thread> event_threads_;
    safe_queue<std::pair<std::shared_ptr<base::event>, http_event_envelope>> event_queue_;
    std::atomic_flag running_;

    void initialize_();
    template <class Event>
    bool route_message_(const Event &message, const token &token);
    void handle_event_(std::shared_ptr<base::event> event, const http_event_envelope &token);
};


template<class EventT>
void http_event_client::on(std::function<void(std::shared_ptr<EventT>, const http_event_envelope &envelope)> func)
{
    handlers_[std::type_index{typeid(EventT)}] = std::unique_ptr<http_event_handler_callback>{
            new http_event_handler_callback_template<EventT>(func)};
}

//This feels...hackish? But it should work.
template<class EventT>
void http_event_client::remove_on()
{
    handlers_.erase(std::type_index{typeid(EventT)});
}
} //namespace slack
