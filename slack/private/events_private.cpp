//
// Created by D.E. Goodman-Wilson on 8/16/16.
//

#include "private.h"
#include "events_private.h"

namespace slack { namespace event
{

void initialize_events(void)
{
    //This is the tedious bit

    slack_private::events_factory.register_type<hello>(hello::type, [](const Json::Value &root)
        {
            return std::make_shared<hello>(root);
        });

    slack_private::events_factory.register_type<user_typing>(user_typing::type, [](const Json::Value &root)
        {
            return std::make_shared<user_typing>(root);
        });

    slack_private::events_factory.register_type<pong>(pong::type, [](const Json::Value &root)
        {
            return std::make_shared<pong>(root);
        });

    slack_private::events_factory.register_type<pong>(message::type, [](const Json::Value &root)
        {
            return std::make_shared<message>(root);
        });
}

}} //namespace events slack