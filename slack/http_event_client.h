//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/event/events.h>
#include <slack/types.h>
#include <typeindex>
#include <string>
#include <vector>
#include <regex>
#include <utility>


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
    http_event_client(verification_token &&verification_token);

    http_event_client(const verification_token &verification_token);

    virtual ~http_event_client() = default;

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
    using handler_map = std::map<std::type_index, std::unique_ptr<http_event_handler_callback>>;
    handler_map handlers_;
    std::function<void(std::string message, std::string received)> error_handler_;
    //let's just brute force this for now
    std::vector<std::pair<std::regex, hears_cb>> callbacks_;

    template <class Event>
    bool route_message_(const Event &message, const token &token);
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
