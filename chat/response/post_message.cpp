//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/chat/response/post_message.h"
#include <json/json.h>

namespace slack
{
namespace chat
{
namespace response
{


const std::map<std::string, enum post_message::error> post_message::error_str_map =
        {
                {"unknown", post_message::error::unknown},
                {"json_parse_failure", post_message::error::json_parse_failure},
                {"invalid_response", post_message::error::invalid_response},
                {"user_specified", post_message::error::user_specified},
                {"channel_not_found", post_message::error::channel_not_found},
                {"not_in_channel", post_message::error::not_in_channel},
                {"is_archived", post_message::error::is_archived},
                {"msg_too_long", post_message::error::msg_too_long},
                {"no_text", post_message::error::no_text},
                {"rate_limited", post_message::error::rate_limited},
                {"not_authed", post_message::error::not_authed},
                {"invalid_auth", post_message::error::invalid_auth},
                {"account_inactive", post_message::error::account_inactive}
        };

//TODO there is a lot of boilerplate code in here too!
post_message::post_message(const std::string &raw_json) :
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
    if (result_ob["message"].isString()) message = {result_ob["message"]};

    return;
}

} //namespace response
} //namespace api
} //namespace slack