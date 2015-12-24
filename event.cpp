//
// Created by D.E. Goodman-Wilson on 12/14/15.
//

#include "slack/event.h"
#include "private.h"
#include <json/json.h>


namespace slack { namespace event
{

void event_handler::handle_event(std::shared_ptr<base::event> event)
{

    auto it = handlers_.find(std::type_index{typeid(*event)});
    if(it != handlers_.end())
    {
        it->second->exec(event);
    }
}

void initialize_events(void)
{
    //This is the tedious bit
    //TODO do we need this?

    slack_private::events_factory.register_type<hello>(hello::event_name, [](const Json::Value& root)
    {
        return std::make_shared<hello>();
    });

    slack_private::events_factory.register_type<user_typing>(user_typing::event_name, [](const Json::Value& root)
    {
        return std::make_shared<user_typing>(root);
    });

    slack_private::events_factory.register_type<pong>(pong::event_name, [](const Json::Value& root)
    {
        return std::make_shared<pong>(root);
    });
}

}} //namespace events slack