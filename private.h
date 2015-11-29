//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <json/json.h>

namespace slack_private
{
struct json_impl
{
    json_impl(const Json::Value& json) : json{json} {}
    Json::Value json;
};
} //namespace slack_private