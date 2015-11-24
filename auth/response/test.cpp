//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "config.h"
#include "slack/auth/response/test.h"
#include <json/json.h>

namespace slack
{
namespace auth
{
namespace response
{

void test::finish_parse(slack::response::json_impl* json)
{
    Json::Value result_ob = json->json;

    if (result_ob["url"].isString()) url = result_ob["url"].asString();
    if (result_ob["team"].isString()) teamname = result_ob["team"].asString();
    if (result_ob["user"].isString()) username = result_ob["user"].asString();
    if (result_ob["team_id"].isString()) team_id = static_cast<class team_id>(result_ob["team_id"].asString()); //TODO Why do I have to do a static cast here?
    if (result_ob["user_id"].isString()) user_id = static_cast<class user_id>(result_ob["user_id"].asString());
}


} //namespace response
} //namespace api
} //namespace slack