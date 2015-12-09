//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include "slack/base/response.h"
#include "slack/config.h"
#include "slack/http.h"
#include <json/json.h>

namespace slack_private
{

Json::Value get(slack::base::response2 *obj, std::string endpoint, slack::http::params params, bool auth = true);

struct json_impl
{
    json_impl(const Json::Value &json) : json{json}
    { }

    Json::Value json;
};
} //namespace slack_private