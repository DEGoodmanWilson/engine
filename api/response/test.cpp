//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/api/response/test.h"
#include <json/json.h>

namespace slack
{
namespace api
{
namespace response
{

test::test(const std::string &raw_json) :
        raw_json{raw_json}, ok{false}
{
    Json::Value result_ob;
    Json::Reader reader;
    bool parsedSuccess = reader.parse(raw_json, result_ob, false);
    if (!parsedSuccess)
    {
        error = error::json_parse_failure;
        error_str = std::string{"json_parse_failure"};
        return;
    }

    if (!result_ob["ok"].isBool())
    {
        error = error::invalid_response;
        error_str = std::string{"invalid_response"};
        return;
    }

    ok = result_ob["ok"].asBool();

    if (!ok)
    {
        //TODO set up a map!;
        //Actually in this case, there are no specified errors, only user specified ones
        error = error::user_specified;
        error_str = result_ob["error"].asString();
        //normally we would return here, but this isn't _actually_ an error condition, there is more work to do!
    }

    if (!result_ob["args"].isNull() && result_ob["args"].isObject())
    {
        args = std::multimap<std::string, std::string>{};

        for (auto arg: result_ob["args"].getMemberNames())
        {
            args->emplace(arg, result_ob["args"][arg].asString());
        }
    }

    return;
}

} //namespace response
} //namespace api
} //namespace slack