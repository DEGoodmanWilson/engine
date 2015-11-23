//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/chat/response/update.h"
#include <json/json.h>

namespace slack
{
namespace chat
{
namespace response
{


const std::map<std::string, enum update::error> update::error_str_map =
        {
                {"unknown", update::error::unknown},
                {"json_parse_failure", update::error::json_parse_failure},
                {"invalid_response", update::error::invalid_response},
                {"user_specified", update::error::user_specified},
                {"channel_not_found", update::error::channel_not_found},
                {"edit_window_closed", update::error::edit_window_closed},
                {"msg_too_long", update::error::msg_too_long},
                {"no_text", update::error::no_text},
                {"not_authed", update::error::not_authed},
                {"invalid_auth", update::error::invalid_auth},
                {"account_inactive", update::error::account_inactive}
        };

//TODO there is a lot of boilerplate code in here too!
update::update(const std::string &raw_json) :
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
        error_str = result_ob["error"].asString();
        error = error_str_map.at(*error_str);
        return;
    }

    if (result_ob["channel"].isString()) channel = result_ob["channel"].asString();
    if (result_ob["ts"].isString()) ts = result_ob["ts"].asString();
    if (result_ob["text"].isString()) text = result_ob["text"].asString();

    return;
}

} //namespace response
} //namespace api
} //namespace slack