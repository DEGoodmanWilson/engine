//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/event/message_channel_archive.h"
#include <json/json.h>

namespace slack { namespace event
{

const std::string message_channel_archive::type{"message.channel_archive"};

template<>
message_channel_archive::message_channel_archive(const slack::team_id &team_id, const Json::Value &parsed_json) : event{team_id, parsed_json}
{
    if (parsed_json["user"].isString()) user = user_id{parsed_json["user"].asString()};
    if (parsed_json["text"].isString()) text = parsed_json["text"].asString();
    if (parsed_json["ts"].isString()) ts = slack::ts{parsed_json["text"].asString()};
    if (parsed_json["members"].isArray())
    {
        for (auto m: parsed_json["members"])
        {
            members.emplace_back(user_id{m.asString()});
        }
    }
}

}} //namespace event slack