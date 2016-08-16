//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/base/event.h>
#include <slack/event/events.h>
#include <typeindex>
#include <map>

namespace slack { namespace event
{

/***
 * Adapted from http://www.gamedev.net/page/resources/_/technical/game-programming/effective-event-handling-in-c-r2459
 */

class event_handler_callback
{
public:
    virtual ~event_handler_callback() = default;

    void exec(std::shared_ptr<slack::base::event> event)
    {
        call(event);
    }

private:
    virtual void call(std::shared_ptr<slack::base::event>) = 0;
};


template<class EventT>
class event_handler_callback_template :
        public event_handler_callback
{
public:
    event_handler_callback_template(std::function<void(std::shared_ptr<EventT>)> memFn) : function_(memFn)
    {};

    void call(std::shared_ptr<slack::base::event> event)
    {
        function_(std::static_pointer_cast<EventT>(event));
    }

private:
    std::function<void(std::shared_ptr<EventT>)> function_;
};


class event_handler
{
public:
    event_handler();

    event_handler(std::string &&token);

    event_handler(const std::string &token);

    virtual ~event_handler() = default;

    void handle_event(const std::string &event);

    template<class EventT>
    void register_event_handler(std::function<void(std::shared_ptr<EventT>)> handler);

    template<class EventT>
    void deregister_event_handler();

    void register_error_handler(std::function<void(std::string message, std::string received)> handler);

    void deregister_error_handler();

private:
    using handler_map = std::map<std::type_index, std::unique_ptr<event_handler_callback>>;
    handler_map handlers_;
    std::function<void(std::string message, std::string received)> error_handler_;
    std::string token_;
};


template<class EventT>
void event_handler::register_event_handler(std::function<void(std::shared_ptr<EventT>)> func)
{
    handlers_[std::type_index{typeid(EventT)}] = std::unique_ptr<event_handler_callback>{
            new event_handler_callback_template<EventT>(func)};
}

//This feels...hackish? But it should work.
template<class EventT>
void event_handler::deregister_event_handler()
{
    handlers_.erase(std::type_index{typeid(EventT)});
}

}} //namespace event slack