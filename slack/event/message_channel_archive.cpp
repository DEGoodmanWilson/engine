//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/event/message.h"
#include <json/json.h>

namespace slack { namespace event
{

const std::string message_channel_archive::name{"message.channel_archive"};

template<>
message_channel_archive::message_channel_archive(const Json::Value &parsed_json)
{
    if (parsed_json["user"].isString()) user = user_id{parsed_json["user"].asString()};
    if (parsed_json["text"].isString()) text = parsed_json["text"].asString();
    if (parsed_json["ts"].isString()) ts = slack::ts{parsed_json["text"].asString()};
    if (parsed_json["members"].isArray())
    {
        for(auto m: parsed_json["members"])
        {
            members.emplace_back(user_id{m.asString()});
        }
    }
}

}} //namespace event slack