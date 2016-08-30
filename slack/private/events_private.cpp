//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "private.h"
#include "events_private.h"

namespace slack { namespace event
{

void initialize_events(void)
{
    //This is the tedious bit

    slack_private::events_factory.register_type<hello>(hello::type, [](const slack::team_id &team_id, const Json::Value &root)
        {
            return std::make_shared<hello>(team_id, root);
        });

    slack_private::events_factory.register_type<user_typing>(user_typing::type, [](const slack::team_id &team_id, const Json::Value &root)
        {
            return std::make_shared<user_typing>(team_id, root);
        });

    slack_private::events_factory.register_type<pong>(pong::type, [](const slack::team_id &team_id, const Json::Value &root)
        {
            return std::make_shared<pong>(team_id, root);
        });

    slack_private::events_factory.register_type<pong>(message::type, [](const slack::team_id &team_id, const Json::Value &root)
        {
            return std::make_shared<message>(team_id, root);
        });
}

}} //namespace events slack