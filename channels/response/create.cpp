//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "config.h"
#include "slack/channels/response/create.h"
#include <json/json.h>

namespace slack
{
namespace channels
{
namespace response
{

void create::finish_parse(slack::response::json_impl* json)
{
    Json::Value result_ob = json->json;

    if (result_ob["channel"].isObject()) channel = slack::channel(result_ob["channel"]);
}


} //namespace response
} //namespace channels
} //namespace slack