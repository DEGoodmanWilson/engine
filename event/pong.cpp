//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/event/pong.h"
#include <json/json.h>

namespace slack { namespace event
{

const std::string pong::event_name{"pong"};

template<>
pong::pong(const Json::Value &parsed_json)
{
    if (parsed_json["reply_to"].isString()) reply_to = {parsed_json["reply_to"].asString()};
    if (parsed_json["time"].isString()) time = {parsed_json["time"].asString()};
}

}} //namespace event slack