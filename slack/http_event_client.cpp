//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "http_event_client.h"
#include "private.h"
#include "events_private.h"
#include "web_client.h"
#include <json/json.h>

/***
 * TODO
 * 1) make receiving message.bot_message in hears handler optional
 * 2) filter out messages from ourselves, making listening for those optional
 */

namespace slack
{

extern logger_cb logger_;


void http_event_client::message::reply(std::string text) const
{
    web_client c{token.bot_token}; //TODO always the bot token? Maybe allow to pick?
    c.chat.postMessage(channel_id, text, chat::postMessage::parameter::as_user{true});
}

http_event_client::~http_event_client()
{
    for(auto &thread : event_threads_)
    {
        running_.clear(); //have to clear this bit for each thread.
        if(thread.joinable()) thread.join(); //TODO Use the CVs to coordinate this stuff!
    }
}

void http_event_client::initialize_()
{
    event::initialize_events();

    running_.test_and_set();

    for(parameter::thread_count i = 0; i < thread_count_; ++i)
    {
        event_threads_.emplace_back(
                [this]()
                {
                    std::pair<std::shared_ptr<base::event>, http_event_envelope> item;

                    //THe logic:
                    // Run while running is true
                    //   wait for the queue to get an item, timeing out after some time.

                    while(this->running_.test_and_set())
                    {
                        if(this->event_queue_.pop(item, thread_timeout_))
                        {
                            this->handle_event_(item.first, item.second);
                            item.first.reset(); //remove our reference to this pointer so we don't hang onto it longer than necessary.
                        }
                    }
                }
        );
    }
}

template<>
bool http_event_client::route_message_(const event::message &message, const token &token)
{
    //TODO I am not super happy with this, and I don't really have a good clue how to improve it.
    for(const auto &handler_pair : callbacks_)
    {
        std::smatch pieces_match;
        auto message_regex = std::get<std::regex>(handler_pair);

        auto callback = std::get<hears_cb>(handler_pair);
        if(std::regex_search(message.text, pieces_match, message_regex))
        {
            //we found it, let's construct a proper message_reply object
            struct message mesg{message.text, message.user, message.channel, token};

            LOG_DEBUG("Calling handler for message " + message.text);
            callback(mesg); //TODO or we could return the retval from the callback, have it return true if handled and false if it chose not to
            return true;
        }
    }

    LOG_DEBUG("Failed to find handler for message " + message.text);
    return false;
}

template<>
bool http_event_client::route_message_(const event::message_bot_message &message, const token &token)
{
    //TODO I am not super happy with this, and I don't really have a good clue how to improve it.
    for(const auto &handler_pair : callbacks_)
    {
        std::smatch pieces_match;
        auto message_regex = std::get<std::regex>(handler_pair);

        auto callback = std::get<hears_cb>(handler_pair);
        if(std::regex_search(message.text, pieces_match, message_regex))
        {
            //we found it, let's construct a proper message_reply object
            struct message mesg{message.text, message.bot_id, message.channel, token};

            LOG_DEBUG("Calling handler for message_bot_message " + message.text);
            callback(mesg); //TODO or we could return the retval from the callback, have it return true if handled and false if it chose not to
            return true;
        }
    }

    LOG_DEBUG("Failed to find handler for message_bot_message " + message.text);
    return false;
}

//TODO I'm not awfully fond of returning a string here, but unsure what else to do!
std::string http_event_client::handle_event(const std::string &event_str, const token &token)
{
    // turn the string into an event object TODO DRY this up!!
    Json::Value envelope_obj;
    Json::Reader reader;
    bool parsed_success = reader.parse(event_str, envelope_obj, false);
    if(!parsed_success)
    {
        LOG_ERROR(std::string{"JSON parse error: "} + event_str);
        if(error_handler_)
        {
            error_handler_("JSON parse error", event_str);
        }
        return "";
    }

    // make sure we have an actual event
    if(!envelope_obj.isObject() || !envelope_obj["type"].isString())
    {
        //we don't.
        LOG_ERROR(std::string{"Invalid event JSON: "} + event_str);
        if(error_handler_)
        {
            error_handler_("Invalid event JSON", event_str);
        }
        return "";
    }

    //Check the token
    if(!verification_token_.empty() && envelope_obj["token"].isString() &&
       (verification_token_ != envelope_obj["token"].asString()))
    {
        // a token was specified, and it doesn't match what we got on the wire
        LOG_ERROR(std::string{"Invalid token on event: "} + event_str);
        if(error_handler_)
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
        LOG_ERROR(std::string{"Unknown event envelope: "} + event_str);
        if(error_handler_)
        {
            error_handler_("Unknown event envelope", event_str);
        }
        return "";
    }

    // construct envelope object. TODO it should know how to construct itself like any other event.
    // TODO make sure the envelope has the other properties!
    http_event_envelope envelope{
            envelope_obj["token"].asString(), //verification_token
            token, //token
            envelope_obj["api_app_id"].asString(), //api_app_id
            {}
    };
    envelope.token.team_id = envelope_obj["team_id"].asString();

    if(!envelope_obj["authed_users"].isNull() && envelope_obj["authed_users"].isArray())
    {
        for(const auto user_obj : envelope_obj["authed_users"])
        {
            envelope.authed_users.emplace_back(user_obj.asString());
        }
    }


    // Extract and examine the event from the event envelope
    Json::Value result_obj = envelope_obj["event"];

    // make sure we have an actual event
    if(!result_obj.isObject() || !result_obj["type"].isString())
    {
        //we don't.
        LOG_ERROR(std::string{"Invalid event JSON: "} + event_str);
        if(error_handler_)
        {
            error_handler_("Invalid event JSON", event_str);
        }
        return "";
    }

    auto type = result_obj["type"].asString();
    if(result_obj["subtype"].isString())
    {
        type += "." + result_obj["subtype"].asString();
    }

    LOG_DEBUG("Received event " + type);

    //TODO make this more elegant
    struct team_id team_id{envelope_obj["team_id"].asString()};

    auto event = slack_private::events_factory.create(type, team_id, result_obj);

    // we didn't recognize this event, create an unknown event
    if(!event)
    {
        event = std::make_shared<event::unknown>(team_id, result_obj);
    }

    // safe_queue it up if threaded
    if(thread_count_)
    {
        event_queue_.push(std::make_pair(event, envelope));
    }
    else
    {
        //not threading, just do it.
        handle_event_(event, envelope);
    }

    return "";
}

void http_event_client::on_error(std::function<void(std::string message, std::string received)> handler)
{
    error_handler_ = handler;
}

void http_event_client::remove_on_error()
{
    error_handler_ = nullptr;
}


void http_event_client::handle_event_(std::shared_ptr<base::event> event, const http_event_envelope &envelope)
{
    // dispatch the event object to the registered event handler, if there is one
    auto it = handlers_.find(std::type_index{typeid(*event)});
    if(it != handlers_.end())
    {
        LOG_DEBUG("Found handler for event of type " + event->str());
        it->second->exec(event, envelope);
    }

    // if this was a message, hand it off to the message handlers
    if(typeid(*event) == typeid(event::message))
    {
        route_message_(dynamic_cast<event::message &>(*event), envelope.token);
    }
    else if(typeid(*event) == typeid(event::message_bot_message))
    {
        route_message_(dynamic_cast<event::message_bot_message &>(*event), envelope.token);
    }
}

} //namespace slack