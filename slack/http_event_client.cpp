//
// Created by D.E. Goodman-Wilson on 8/16/16.
//

#include "http_event_client.h"
#include "private.h"
#include "events_private.h"
#include <json/json.h>

namespace slack
{

http_event_client::http_event_client()
{
    event::initialize_events();
}

http_event_client::http_event_client(const std::string &token) : token_{token}
{
    event::initialize_events();
}

http_event_client::http_event_client(std::string &&token) : token_{std::move(token)}
{
    event::initialize_events();
}

//TODO I'm not awfully fond of returning a string here, but unsure what else to do!
std::string http_event_client::handle_event(const std::string &event_str)
{
    // turn the string into an event object TODO DRY this up!!
    Json::Value envelope_obj;
    Json::Reader reader;
    bool parsed_success = reader.parse(event_str, envelope_obj, false);
    if (!parsed_success)
    {
        // TODO should log this
        if (error_handler_)
        {
            error_handler_("JSON parse error", event_str);
        }
        return "";
    }

    // make sure we have an actual event
    if (!envelope_obj.isObject() || !envelope_obj["type"].isString())
    {
        //we don't. TODO log it?
        if (error_handler_)
        {
            error_handler_("Invalid event JSON", event_str);
        }
        return "";
    }

    //Check the token
    if (!token_.empty() && envelope_obj["token"].isString() && (token_ != envelope_obj["token"].asString()))
    {
        // a token was specified, and it doesn't match what we got on the wire
        //TODO log it
        if (error_handler_)
        {
            error_handler_("Invalid token on event", event_str);
        }
        return "";
    }

    auto envelope_type = envelope_obj["type"].asString();
    //This will be one of two things `url_verification` or `event_callback`

    //TODO branching here
    if(envelope_type == "url_verification")
    {
        //TODO special handling here! This is the only event that requires a _response_!
        //TODO verify that this property exists.
        return envelope_obj["challenge"].asString();
    }

    else if(envelope_type != "event_callback")
    {
        // a token was specified, and it doesn't match what we got on the wire
        //TODO log it
        if (error_handler_)
        {
            error_handler_("Unknown event envelope", event_str);
        }
        return "";
    }

    // construct envelope object. TODO it should know how to construct itself like any other event.
    // TODO make sure the envelope has the other properties!
    http_event_envelope envelope{
            envelope_obj["token"].asString(),
            {envelope_obj["team_id"].asString()},
            envelope_obj["api_app_id"].asString(),
            envelope_obj["event_ts"].asString(),
            {}
    };

    if (!envelope_obj["authed_users"].isNull() && envelope_obj["authed_users"].isArray())
    {
        for (const auto user_obj : envelope_obj["authed_users"])
        {
            envelope.authed_users.emplace_back(user_obj.asString());
        }
    }


    // Extract and examine the event from the event envelope
    Json::Value result_obj = envelope_obj["event"];

    // make sure we have an actual event
    if (!result_obj.isObject() || !result_obj["type"].isString())
    {
        //we don't. TODO log it?
        if (error_handler_)
        {
            error_handler_("Invalid event JSON", event_str);
        }
        return "";
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
        it->second->exec(event, envelope);
        return "";
    }

    //TODO log failure to find matching handler
    return "";
}

void http_event_client::register_error_handler(std::function<void(std::string message, std::string received)> handler)
{
    error_handler_ = handler;
}

void http_event_client::deregister_error_handler()
{
    error_handler_ = nullptr;
}

} //namespace slack