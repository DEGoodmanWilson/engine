//
// Created by D.E. Goodman-Wilson on 12/14/15.
//

#include "slack/event.h"
#include "private.h"
#include "events_private.h"
#include <json/json.h>


namespace slack { namespace event
{


event_handler::event_handler()
{
    event::initialize_events();
}


void event_handler::handle_event(const std::string &event_str)
{
    // turn the string into an event object
    Json::Value result_ob;
    Json::Reader reader;
    bool parsed_success = reader.parse(event_str, result_ob, false);
    if (!parsed_success)
    {
        // TODO should log this
        if(error_handler_)
        {
            error_handler_("JSON parse error", event_str);
        }
        return;
    }

    // make sure we have an actual event
    if (!result_ob.isObject() || !result_ob["type"].isString())
    {
        //we don't. TODO log it?
        if(error_handler_)
        {
            error_handler_("Invalid event JSON", event_str);
        }
        return;
    }

    auto type = result_ob["type"].asString();
    if(result_ob["subtype"].isString())
    {
        type += "."+result_ob["subtype"].asString();
    }
    auto event = slack_private::events_factory.create(type, result_ob);

    // we didn't recognize this event, create an unknown event
    if(!event) event = std::make_shared<event::unknown>(type);

    // dispatch the event object to all registered event handlers
    auto it = handlers_.find(std::type_index{typeid(*event)});
    if(it != handlers_.end())
    {
        it->second->exec(event);
    }
}

void event_handler::register_error_handler(std::function<void(std::string &&message, const std::string received)> handler)
{
    error_handler_ = handler;
}

void event_handler::deregister_error_handler()
{
    error_handler_ = nullptr;
}

}} //namespace events slack