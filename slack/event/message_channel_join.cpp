//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/event/message_channel_join.h"
#include <json/json.h>

namespace slack { namespace event
{

const std::string message_channel_join::type{"message.channel_join"};

template<>
message_channel_join::message_channel_join(const slack::team_id &team_id, const Json::Value &parsed_json) :
        event{team_id, parsed_json}
{
    if(parsed_json["user"].isString())
    {
        user = user_id{parsed_json["user"].asString()};
    }
    if(parsed_json["text"].isString())
    {
        text = parsed_json["text"].asString();
    }
    if(parsed_json["ts"].isString())
    {
        ts = slack::ts{parsed_json["text"].asString()};
    }
    if(parsed_json["channel"].isString())
    {
        channel = slack::channel_id{parsed_json["channel"].asString()};
    }
    if(parsed_json["inviter"].isString())
    {
        inviter = slack::user_id{parsed_json["inviter"].asString()};
    }
}

}} //namespace event slack