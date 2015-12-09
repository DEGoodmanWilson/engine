//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/base/response.h"
#include "private.h"
#include <json/json.h>

namespace slack
{
namespace base
{

const std::string error::UNKNOWN = "unknown";
const std::string error::JSON_PARSE_FAILURE = "json_parse_failure";
const std::string error::INVALID_RESPONSE = "invalid_response";

response::response(const std::string &raw_json) : raw_json{raw_json}, json_{nullptr}
{
    Json::Value result_ob;
    Json::Reader reader;
    bool parsed_success = reader.parse(raw_json, result_ob, false);
    if (!parsed_success)
    {
        error = std::string{"json_parse_failure"};
        return;
    }

    if (!result_ob["ok"].isBool())
    {
        error = std::string{"invalid_response"};
        return;
    }

    auto ok = result_ob["ok"].asBool();

    if (!ok)
    {
        error = result_ob["error"].asString();
    }

    json_ = new slack_private::json_impl(result_ob);
}

response::~response()
{
    delete json_;
}


} //namespace base
} //namespace slack
