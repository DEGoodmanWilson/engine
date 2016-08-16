//
// Created by D.E. Goodman-Wilson on 8/16/16.
//

#pragma once

#include <slack/event/events.h>
#include <slack/types.h>
#include <typeindex>
#include <string>
#include <vector>

namespace slack
{

struct http_event_envelope
{
    std::string token;
    team_id team_id;
    std::string api_app_id;
    ts event_ts;
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
    http_event_client();

    http_event_client(std::string &&token);

    http_event_client(const std::string &token);

    virtual ~http_event_client() = default;

    virtual std::string handle_event(const std::string &event);

    template<class EventT>
    void register_event_handler(std::function<void(std::shared_ptr<EventT>, const http_event_envelope& envelope)> handler);

    template<class EventT>
    void deregister_event_handler();

    void register_error_handler(std::function<void(std::string message, std::string received)> handler);

    void deregister_error_handler();

protected:
    using handler_map = std::map<std::type_index, std::unique_ptr<http_event_handler_callback>>;
    handler_map handlers_;
    std::function<void(std::string message, std::string received)> error_handler_;
    std::string token_;
};


template<class EventT>
void http_event_client::register_event_handler(std::function<void(std::shared_ptr<EventT>, const http_event_envelope& envelope)> func)
{
    handlers_[std::type_index{typeid(EventT)}] = std::unique_ptr<http_event_handler_callback>{
            new http_event_handler_callback_template<EventT>(func)};
}

//This feels...hackish? But it should work.
template<class EventT>
void http_event_client::deregister_event_handler()
{
    handlers_.erase(std::type_index{typeid(EventT)});
}
} //namespace slack