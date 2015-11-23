//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/channels/response/list.h"
#include <json/json.h>

namespace slack
{
namespace channels
{
namespace response
{

const std::map<std::string, enum list::error> list::error_str_map =
        {
                {"unknown",            list::error::unknown},
                {"json_parse_failure", list::error::json_parse_failure},
                {"invalid_response",   list::error::invalid_response},
                {"not_authed",         list::error::not_authed},
                {"invalid_auth",       list::error::invalid_auth},
                {"account_inactive",   list::error::account_inactive}
        };

list::list(const std::string &raw_json) : raw_json{raw_json}
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
        error_str = result_ob["error"].asString();
        error = error_str_map.at(*error_str);
        return;
    }

    for (const auto channel_obj : result_ob["channels"])
    {
        channels.emplace_back(channel_obj);
    }
}


} //namespace response
} //namespace channels
} //namespace slack