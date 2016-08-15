//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/event/channel_archive.h"
#include <json/json.h>

namespace slack { namespace event
{

const std::string channel_archive::name{"channel_archive"};

template<>
channel_archive::channel_archive(const Json::Value &parsed_json) : event{parsed_json}
{
    if (parsed_json["channel"].isString()) channel = channel_id{parsed_json["channel"].asString()};
    if (parsed_json["user"].isString()) user = user_id{parsed_json["user"].asString()};
}

}} //namespace event slack