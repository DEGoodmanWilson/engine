//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/event/channel_archive.h"
#include <json/json.h>

namespace slack { namespace event
{

const std::string channel_archive::type{"channel_archive"};

template<>
channel_archive::channel_archive(const slack::team_id &team_id, const Json::Value &parsed_json) : event{team_id, parsed_json}
{
    if (parsed_json["channel"].isString()) channel = channel_id{parsed_json["channel"].asString()};
    if (parsed_json["user"].isString()) user = user_id{parsed_json["user"].asString()};
}

}} //namespace event slack