//
// Created by D.E. Goodman-Wilson on 12/14/15.
//

#include "slack/event.h"
#include <json/json.h>

namespace slack { namespace event
{

template<>
user_typing::user_typing(const Json::Value &parsed_json)
{
    if (parsed_json["channel"].isString()) channel = channel_id{parsed_json["channel"].asString()};
    if (parsed_json[""].isString()) user = user_id{parsed_json["user"].asString()};
}

}} //namespace events slack