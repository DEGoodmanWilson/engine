//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/event/unknown.h"
#include <json/json.h>

namespace slack { namespace event
{
template<>
unknown::unknown(const slack::team_id &team_id, const Json::Value &parsed_json) : event{team_id, parsed_json}
{
    if (parsed_json["type"].isString()) type = parsed_json["type"].asString();
}

}} //namespace event slack