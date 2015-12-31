//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/base/event.h>
#include <typeindex>
#include <map>


#include <slack/event/hello.h>
#include <slack/event/user_typing.h>
#include <slack/event/pong.h>
#include <slack/event/channel_archive.h>
#include <slack/event/message.h>
#include <slack/event/message/channel_archive.h>

namespace slack { namespace event
{

/***
 * Adapted from http://www.gamedev.net/page/resources/_/technical/game-programming/effective-event-handling-in-c-r2459
 */

template<class EventT>
class event_handler_callback_template :
        public base::event_handler_callback
{
public:
    event_handler_callback_template(std::function<void(std::shared_ptr<EventT>)> memFn) : function_(memFn)
    { };

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
    virtual ~event_handler() = default;

    void handle_event(std::shared_ptr<slack::base::event> event);

    template<class EventT>
    void register_event_handler(std::function<void(std::shared_ptr<EventT>)>);
    template<class EventT>
    void deregister_event_handler();

private:
    using handler_map = std::map<std::type_index, std::unique_ptr<base::event_handler_callback>>; //TODO make unique_ptr!
    handler_map handlers_;
};


template<class EventT>
void event_handler::register_event_handler(std::function<void(std::shared_ptr<EventT>)> func)
{
    handlers_[std::type_index{typeid(EventT)}] = std::unique_ptr<base::event_handler_callback>{
            new event_handler_callback_template<EventT>(func)};
}

//This feels...hackish? But it should work.
template <class EventT>
void event_handler::deregister_event_handler()
{
    handlers_.erase(std::type_index{typeid(EventT)});
}

}} //namespace event slack