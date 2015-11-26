//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "config.h"
#include "slack/channels/response/archive.h"
#include <json/json.h>

namespace slack
{
namespace channels
{
namespace response
{

void archive::finish_parse(slack::response::json_impl* json)
{
    Json::Value result_ob = json->json;

    //there is literally nothing else in the response.
}


} //namespace response
} //namespace channels
} //namespace slack