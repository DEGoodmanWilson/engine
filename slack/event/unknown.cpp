//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/event/unknown.h"
#include <json/json.h>
#include <sstream>

namespace slack { namespace event
{
template<>
unknown::unknown(const slack::team_id &team_id, const Json::Value &parsed_json) : event{team_id, parsed_json}
{
    if (parsed_json["type"].isString()) type = parsed_json["type"].asString();
    if (parsed_json["subtype"].isString()) type += "." + parsed_json["subtype"].asString();

    std::stringstream strstr;
    strstr << parsed_json;
    raw_event = strstr.str();
}

}} //namespace event slack