//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <string>
#include <cpr.h>
#include <json/json.h>

namespace slack_config
{
const std::string HOSTNAME = "https://slack.com/api/";
}


//TODO move this into a different header. This is silly
namespace slack
{
namespace base
{
struct json_impl
{
    json_impl(const Json::Value& json) : json{json} {}
    Json::Value json;
};

}
}