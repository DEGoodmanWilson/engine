//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/event/message.h"
#include <json/json.h>

namespace slack { namespace event { namespace message_subtype
{

const std::string channel_archive::event_name{"message.channel_archive"};

template<>
channel_archive::channel_archive(const Json::Value &parsed_json)
{
    if (parsed_json["user"].isString()) user = user_id{parsed_json["user"].asString()};
    if (parsed_json["text"].isString()) text = parsed_json["text"].asString();
    if (parsed_json["ts"].isString()) ts = slack::ts{parsed_json["text"].asString()};
    if (parsed_json["members"].isArray())
    {
        members = std::vector<user_id>{};
        for(auto m: parsed_json["members"])
        {
            members->emplace_back(user_id{m.asString()});
        }
    }
}

}}} //namespace message_subtype event slack