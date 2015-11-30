//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/types.h"
#include <json/json.h>

namespace slack
{

//overload for our own json type. Clever way to get around exposing the json.h file in public interfaces. I hope.
template<>
channel::channel(const Json::Value &parsed_json) :
        id{parsed_json["id"].asString()},
        name{parsed_json["name"].asString()},
        is_channel{parsed_json["is_channel"].asBool()},
        created{parsed_json["created"].asInt()},
        creator{parsed_json["creator"].asString()},
        is_archived{parsed_json["is_archived"].asBool()},
        is_general{parsed_json["is_general"].asBool()},
        is_member{parsed_json["is_member"].asBool()},
        last_read{parsed_json["last_read"].asString()},
        unread_count{parsed_json["unread_count"].asInt()},
        unread_display_count{parsed_json["unread_display_count"].asInt()}
{
    for(const auto member_obj : parsed_json["members"])
    {
        members.emplace_back(member_obj.asString());
    }
    topic = {
            parsed_json["topic"]["value"].asString(),
            parsed_json["topic"]["creator"].asString(),
            parsed_json["topic"]["last_set"].asInt()
    };
    purpose = {
            parsed_json["purpose"]["value"].asString(),
            parsed_json["purpose"]["creator"].asString(),
            parsed_json["purpose"]["last_set"].asInt()
    };
}

template<>
message::message(const Json::Value &parsed_json)
{
    text = parsed_json["text"].asString();

    //TODO this needs more nuance.
    ts = parsed_json["ts"].asString();

    //TODO these are going to be optional probably
    username = parsed_json["username"].asString();
    type = parsed_json["type"].asString();
    if (!parsed_json["subtype"].isNull())
    {
        subtype = parsed_json["subtype"].asString();
    }
}

}