//
// Created by D.E. Goodman-Wilson on 8/16/16.
//

#pragma once

#include <slack/event/events.h>
#include <typeindex>

namespace slack
{

class rtm_event_handler_callback
{
public:
    virtual ~rtm_event_handler_callback() = default;

    void exec(std::shared_ptr<slack::base::event> event)
    {
        call(event);
    }

private:
    virtual void call(std::shared_ptr<slack::base::event>) = 0;
};


template<class EventT>
class rtm_event_handler_callback_template :
        public rtm_event_handler_callback
{
public:
    rtm_event_handler_callback_template(std::function<void(std::shared_ptr<EventT>)> memFn) : function_(memFn)
    {};

    void call(std::shared_ptr<slack::base::event> event)
    {
        function_(std::static_pointer_cast<EventT>(event));
    }

private:
    std::function<void(std::shared_ptr<EventT>)> function_;
};


class rtm_event_client
{
public:
    rtm_event_client();

    rtm_event_client(std::string &&token);

    rtm_event_client(const std::string &token);

    virtual ~rtm_event_client() = default;

    virtual void handle_event(const std::string &event);

    template<class EventT>
    void register_event_handler(std::function<void(std::shared_ptr<EventT>)> handler);

    template<class EventT>
    void deregister_event_handler();

    void register_error_handler(std::function<void(std::string message, std::string received)> handler);

    void deregister_error_handler();

protected:
    using handler_map = std::map<std::type_index, std::unique_ptr<rtm_event_handler_callback>>;
    handler_map handlers_;
    std::function<void(std::string message, std::string received)> error_handler_;
};


template<class EventT>
void rtm_event_client::register_event_handler(std::function<void(std::shared_ptr<EventT>)> func)
{
    handlers_[std::type_index{typeid(EventT)}] = std::unique_ptr<rtm_event_handler_callback>{
            new rtm_event_handler_callback_template<EventT>(func)};
}

//This feels...hackish? But it should work.
template<class EventT>
void rtm_event_client::deregister_event_handler()
{
    handlers_.erase(std::type_index{typeid(EventT)});
}
} //namespace slack