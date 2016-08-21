//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/event/message_bot_message.h"
#include <json/json.h>

namespace slack { namespace event
{

const std::string message_bot_message::type{"message.bot_message"};

template<>
message_bot_message::message_bot_message(const slack::team_id &team_id, const Json::Value &parsed_json) : event{team_id, parsed_json}, is_starred{false}
{
    if (parsed_json.isNull()) return;

    if (parsed_json["channel"].isString()) channel = channel_id{parsed_json["channel"].asString()};
    if (parsed_json["bot_id"].isString()) bot_id = user_id{parsed_json["bot_id"].asString()};
    if (parsed_json["text"].isString()) text = parsed_json["text"].asString();
    if (parsed_json["ts"].isString()) ts = slack::ts{parsed_json["text"].asString()};
    if (parsed_json["is_starred"].isString()) is_starred = parsed_json["is_starred"].asBool();
    if (parsed_json["pinned_to"].isArray())
    {
        for (auto p: parsed_json["pinned_to"])
        {
            pinned_to.emplace_back(channel_id{p.asString()});
        }
    }
    if (parsed_json["reactions"].isArray())
    {
        for (auto r: parsed_json["reactions"])
        {
            reactions.emplace_back(reaction{r});
        }
    }
}

}} //namespace event slack