//
// Created by D.E. Goodman-Wilson on 8/16/16.
//

#include "rtm_event_client.h"
#include "private.h"
#include "events_private.h"
#include <json/json.h>

namespace slack
{

rtm_event_client::rtm_event_client()
{
    event::initialize_events();
}


void rtm_event_client::handle_event(const std::string &event_str)
{
    // turn the string into an event object
    Json::Value result_obj;
    Json::Reader reader;
    bool parsed_success = reader.parse(event_str, result_obj, false);
    if (!parsed_success)
    {
        // TODO should log this
        if (error_handler_)
        {
            error_handler_("JSON parse error", event_str);
        }
        return;
    }

    // make sure we have an actual event
    if (!result_obj.isObject() || !result_obj["type"].isString())
    {
        //we don't. TODO log it?
        if (error_handler_)
        {
            error_handler_("Invalid event JSON", event_str);
        }
        return;
    }

    auto type = result_obj["type"].asString();
    if (result_obj["subtype"].isString())
    {
        type += "." + result_obj["subtype"].asString();
    }
    auto event = slack_private::events_factory.create(type, result_obj);

    // we didn't recognize this event, create an unknown event
    if (!event)
    {
        event = std::make_shared<event::unknown>(result_obj);
    }

    // dispatch the event object to the registered event handler, if there is one
    auto it = handlers_.find(std::type_index{typeid(*event)});
    if (it != handlers_.end())
    {
        it->second->exec(event);
        return;
    }

    //TODO log failure to find matching handler
}

void rtm_event_client::register_error_handler(std::function<void(std::string message, std::string received)> handler)
{
    error_handler_ = handler;
}

void rtm_event_client::deregister_error_handler()
{
    error_handler_ = nullptr;
}

} //namespace slack