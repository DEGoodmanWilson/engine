//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/response/base.h"
#include "config.h"
#include <json/json.h>
#include <string>

namespace slack
{
namespace response
{

void base::parse(bool do_return)
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
        if(do_return) return;
    }
    json_impl json{result_ob};
    finish_parse(&json); //this is safe because the caller isn't hanging on to it.
}


} //namespace response
} //namespace slack