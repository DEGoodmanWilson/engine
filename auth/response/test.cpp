//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/auth/response/test.h"
#include <json/json.h>

namespace slack
{
namespace auth
{
namespace response
{


const std::map<std::string, enum test::error> test::error_str_map =
        {
                {"unknown",            test::error::unknown},
                {"json_parse_failure", test::error::json_parse_failure},
                {"invalid_response",   test::error::invalid_response},
                {"not_authed",         test::error::not_authed},
                {"invalid_auth",       test::error::invalid_auth},
                {"account_inactive",   test::error::account_inactive}
        };

test::test(const std::string &raw_json) :
        raw_json{raw_json}, ok{false}, error{error::unknown}, error_str{"unknown"}
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
        error_str = result_ob["error"].asString();
        error = error_str_map.at(*error_str);
        return;
    }

    //TODO more rigorous testing
    if (result_ob["url"].isString()) url = result_ob["url"].asString();
    if (result_ob["team"].isString()) teamname = result_ob["team"].asString();
    if (result_ob["user"].isString()) username = result_ob["user"].asString();
    if (result_ob["team_id"].isString()) team_id = static_cast<class team_id>(result_ob["team_id"].asString()); //TODO Why do I have to do a static cast here?
    if (result_ob["user_id"].isString()) user_id = static_cast<class user_id>(result_ob["user_id"].asString());

    return;
}

} //namespace response
} //namespace api
} //namespace slack