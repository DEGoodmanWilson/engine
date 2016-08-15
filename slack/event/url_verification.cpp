//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/event/url_verification.h"
#include <json/json.h>

namespace slack { namespace event
{

const std::string url_verification::name{"url_verification"};

template<>
url_verification::url_verification(const Json::Value &parsed_json) : event{parsed_json}
{
    if (parsed_json.isNull()) return;

    if (parsed_json["challenge"].isString()) challenge = parsed_json["challenge"].asString();
}

}} //namespace event slack