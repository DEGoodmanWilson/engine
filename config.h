//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <string>
#include <json/json.h>

namespace slack_config
{
const std::string HOSTNAME = "https://slack.com/api/";
}

namespace slack
{
namespace response
{
struct json_impl
{
    Json::Value json;
};

}
}