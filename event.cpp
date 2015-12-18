//
// Created by D.E. Goodman-Wilson on 12/14/15.
//

#include "slack/event.h"
#include "private.h"
#include <json/json.h>

namespace slack { namespace event
{

void initialize_events(void)
{
    //This is the tedious bit

    slack_private::events_factory.register_type<hello>(hello::type, [](const Json::Value& root)
    {
        return std::make_shared<hello>();
    });

    slack_private::events_factory.register_type<user_typing>(user_typing::type, [](const Json::Value& root)
    {
        return std::make_shared<user_typing>(root);
    });
}


}} //namespace events slack