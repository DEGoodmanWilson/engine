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

    if (result_ob["url"].isString()) url = result_ob["url"].asString();

    if (!result_ob["channels"].isNull() && result_ob["channels"].isArray())
    {
        channels = std::vector<::slack::channel>{};
        for (const auto channel_obj : result_ob["channels"])
        {
            channels->emplace_back(channel_obj);
        }
    }

    //TODO: There is a lot of work left to be done here!

}

} //namespace response
} //namespace rtm
} //namespace slack