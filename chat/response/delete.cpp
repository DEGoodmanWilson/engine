//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/chat/response/delete.h"
#include <json/json.h>

namespace slack
{
namespace chat
{
namespace response
{


const std::map<std::string, enum delete_it::error> delete_it::error_str_map =
        {
                {"unknown", delete_it::error::unknown},
                {"json_parse_failure", delete_it::error::json_parse_failure},
                {"invalid_response", delete_it::error::invalid_response},
                {"message_not_found", delete_it::error::message_not_found},
                {"channel_not_found", delete_it::error::channel_not_found},
                {"cant_delete_message", delete_it::error::cant_delete_message},
                {"compliance_exports_prevent_deletion", delete_it::error::compliance_exports_prevent_deletion},
                {"not_authed", delete_it::error::not_authed},
                {"invalid_auth", delete_it::error::invalid_auth},
                {"account_inactive", delete_it::error::account_inactive}
        };

//TODO there is a lot of boilerplate code in here too!
delete_it::delete_it(const std::string &raw_json) :
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

    return;
}

} //namespace response
} //namespace api
} //namespace slack