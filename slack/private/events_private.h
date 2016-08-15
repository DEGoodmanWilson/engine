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
    //TODO do we need this?

    slack_private::events_factory.register_type<hello>(hello::name, [](const Json::Value &root) {
        return std::make_shared<hello>();
    });

    slack_private::events_factory.register_type<user_typing>(user_typing::name, [](const Json::Value &root) {
        return std::make_shared<user_typing>(root);
    });

    slack_private::events_factory.register_type<pong>(pong::name, [](const Json::Value &root) {
        return std::make_shared<pong>(root);
    });
    slack_private::events_factory.register_type<pong>(message::name, [](const Json::Value &root) {
        return std::make_shared<message>(root);
    });
}

}} //namespace event slack