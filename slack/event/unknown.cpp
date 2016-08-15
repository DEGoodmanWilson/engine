//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/event/unknown.h"
#include <json/json.h>

namespace slack { namespace event
{
template<>
unknown::unknown(const Json::Value &parsed_json) : event{parsed_json}
{
    if (parsed_json["type"].isString()) name = parsed_json["type"].asString();
}

}} //namespace event slack