//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/chat/response/delete.h"
#include "config.h"
#include <json/json.h>

namespace slack
{
namespace chat
{
namespace response
{

void delete_it::finish_parse(slack::response::json_impl* json)
{
    Json::Value result_ob = json->json;

    if (result_ob["channel"].isString()) channel = result_ob["channel"].asString();
    if (result_ob["ts"].isString()) ts = result_ob["ts"].asString();
}

} //namespace response
} //namespace chat
} //namespace slack