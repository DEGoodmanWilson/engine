//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/event/user_typing.h"
#include <json/json.h>

namespace slack { namespace event
{

const std::string user_typing::name{"user_typing"};

template<>
user_typing::user_typing(const Json::Value &parsed_json)
{
    if (parsed_json["channel"].isString()) channel = channel_id{parsed_json["channel"].asString()};
    if (parsed_json["user"].isString()) user = user_id{parsed_json["user"].asString()};
}

}} //namespace event slack