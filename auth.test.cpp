//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/auth.test.h"
#include "slack/http.h"
#include "private.h"
#include <json/json.h>

namespace slack
{

Json::Value get(slack::base::response2* obj, std::string endpoint, http::params params, bool auth=true)
{
    Json::Value result_ob;

    if(auth)
    {
        params["token"] = ::slack::get_token();
    }
    auto response = http::get(config::HOSTNAME+endpoint, params);
    if(response.status_code != 200)
    {
        //TODO do something!
        obj->error_message = std::string{"TODO"};
        return result_ob;
    }

    Json::Reader reader;
    bool parsed_success = reader.parse(response.body, result_ob, false);
    if (!parsed_success)
    {
        obj->error_message = std::string{"json_parse_failure"};
        return result_ob;
    }

    if (!result_ob["ok"].isBool())
    {
        obj->error_message = std::string{"invalid_response"};
        return result_ob;
    }

    auto ok = result_ob["ok"].asBool();

    if (!ok)
    {
        obj->error_message = result_ob["error"].asString();
        return result_ob;
    }

    return result_ob;
}

namespace auth
{

const std::string test::error::UNKNOWN = std::string{"unknown"};
const std::string test::error::JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const std::string test::error::INVALID_RESPONSE = std::string{"invalid_response"};
const std::string test::error::NOT_AUTHED = std::string{"not_authed"};
const std::string test::error::INVALID_AUTH = std::string{"invalid_auth"};
const std::string test::error::ACCOUNT_INACTIVE = std::string{"account_inactive"};



test::test()
{
    auto result_ob = get(this, "auth.test", {});
    if(!this->error_message)
    {
        if (result_ob["url"].isString()) url = result_ob["url"].asString();
        if (result_ob["team"].isString()) teamname = result_ob["team"].asString();
        if (result_ob["user"].isString()) username = result_ob["user"].asString();
        if (result_ob["team_id"].isString()) team_id = slack::team_id{result_ob["team_id"].asString()};
        if (result_ob["user_id"].isString()) user_id = slack::user_id{result_ob["user_id"].asString()};
    }
}

} //namespace auth
} //namespace slack