//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/api.h"
#include "config.h"
#include <cpr.h>
#include <json/json.h>

namespace slack
{
namespace api
{
namespace impl
{

::slack::api::response::test test::get_response()
{
    cpr::Parameters params; //no need for a token here
    if (!error_.empty())
    {
        params.AddParameter({"error", error_});
    }
    if (!foo_.empty())
    {
        params.AddParameter({"foo", foo_});
    }
    auto result = cpr::Get(cpr::Url{slack_config::HOSTNAME + "api.test"}, params);
    if (result.status_code != 200)
    {
        //error path
        return {result.text}; //TODO
    }
    //happy path
    Json::Value result_ob;
    Json::Reader reader;
    bool parsedSuccess = reader.parse(result.text, result_ob, false);
    if (!parsedSuccess)
    {
        return {result.text}; //TODO
    }

    response::test ret{result.text};

    ret.ok = result_ob["ok"].asBool();

    if (!ret)
    {
        ret.error_str = result_ob["error"].asString();
    }

    if (!result_ob["args"].isNull() && result_ob["args"].isObject())
    {
        std::multimap<std::string, std::string> args;
        for (const auto arg: result_ob["args"].getMemberNames())
        {
            args.emplace(arg, result_ob["args"][arg].asString());
        }
        ret.args = args;
    }

    return ret;
}

} //namespace impl
} //namespace api
} //namespace slack
