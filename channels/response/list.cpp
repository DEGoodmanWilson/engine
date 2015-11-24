//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "config.h"
#include "slack/channels/response/list.h"
#include <json/json.h>

namespace slack
{
namespace channels
{
namespace response
{

void list::finish_parse(slack::response::json_impl* json)
{
    Json::Value result_ob = json->json;

    for (const auto channel_obj : result_ob["channels"])
    {
        channels.emplace_back(channel_obj);
    }
}


} //namespace response
} //namespace channels
} //namespace slack