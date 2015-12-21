//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/base/event.h>
#include <slack/type_info.h>
#include <map>


#include <slack/event/hello.h>
#include <slack/event/user_typing.h>

namespace slack { namespace event
{

/***
 * Adapted from http://www.gamedev.net/page/resources/_/technical/game-programming/effective-event-handling-in-c-r2459
 */

template <class EventT>
class event_handler_callback_template : public base::event_handler_callback
{
public:
    event_handler_callback_template(std::function<void(std::shared_ptr<EventT>)> memFn) : function_(memFn) {};

    void call(std::shared_ptr<slack::base::event> event)
    {
        auto event_cast = std::static_pointer_cast<std::shared_ptr<EventT>>(event);
        function_(event_cast);
    }

private:
    std::function<void(std::shared_ptr<EventT>)> function_;
};

class event_handler
{
public:
    ~event_handler();
    void handle_event(std::shared_ptr<slack::base::event> event);

    template <class EventT>
    void register_event_handler(std::function<void(std::shared_ptr<EventT>)>);

private:
    using handler_map = std::map<type_info, base::event_handler_callback*>; //TODO make unique_ptr!
    handler_map handlers_;
};


template <class EventT>
void event_handler::register_event_handler(std::function<void(std::shared_ptr<EventT>)> func)
{
    handlers_[type_info(typeid(EventT))]= new event_handler_callback_template<EventT>(func);
}

}} //namespace event slack