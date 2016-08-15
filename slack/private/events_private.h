//
// Created by D.E. Goodman-Wilson on 8/15/16.
//

#pragma once

#include <json/json.h>
#include "event/hello.h"
#include "event/user_typing.h"
#include "event/pong.h"
#include "event/channel_archive.h"
#include "event/message.h"
#include "event/message_channel_archive.h"
#include "event/unknown.h"

namespace slack { namespace event
{

void initialize_events(void)
{
    //This is the tedious bit

    slack_private::events_factory.register_type<hello>(hello::type, [](const Json::Value &root) {
        return std::make_shared<hello>(root);
    });

    slack_private::events_factory.register_type<user_typing>(user_typing::type, [](const Json::Value &root) {
        return std::make_shared<user_typing>(root);
    });

    slack_private::events_factory.register_type<pong>(pong::type, [](const Json::Value &root) {
        return std::make_shared<pong>(root);
    });

    slack_private::events_factory.register_type<pong>(message::type, [](const Json::Value &root) {
        return std::make_shared<message>(root);
    });
}

}} //namespace event slack