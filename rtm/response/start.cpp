//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/rtm/response/start.h"
#include "config.h"
#include <json/json.h>

namespace slack
{
namespace rtm
{
namespace response
{

void start::finish_parse(slack::response::json_impl* json)
{
    Json::Value result_ob = json->json;


}

} //namespace response
} //namespace rtm
} //namespace slack