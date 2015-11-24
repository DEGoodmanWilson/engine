//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/api/response/test.h"
#include "config.h"
#include <json/json.h>

namespace slack
{
namespace api
{
namespace response
{

void test::finish_parse(slack::response::json_impl* json)
{
    Json::Value result_ob = json->json;

    if (!result_ob["args"].isNull() && result_ob["args"].isObject())
    {
        args = std::map<std::string, std::string>{};

        for (auto arg: result_ob["args"].getMemberNames())
        {
            args->emplace(arg, result_ob["args"][arg].asString());
        }
    }
}

} //namespace response
} //namespace api
} //namespace slack