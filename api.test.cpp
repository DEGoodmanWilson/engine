//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/api.test.h"
#include "slack/http.h"
#include "private.h"
#include <json/json.h>

namespace slack
{
namespace api
{


/*************************************************************/
// MARK: - Response

namespace response
{

test::test(const std::string &raw_json)
        : slack::base::response{raw_json}
{
    Json::Value result_ob = json_->json;

    if (!result_ob["args"].isNull() && result_ob["args"].isObject())
    {
        args = std::map<std::string, std::string>{};

        for (auto arg: result_ob["args"].getMemberNames())
        {
            args->emplace(arg, result_ob["args"][arg].asString());
        }
    }
}

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

response::test test::get_response()
{
    http::params params;

    if (error_)
    {
        params.emplace("error", *error_);
    }
    if (foo_)
    {
        params.emplace("foo", *foo_);
    }

    return get("api.test", params);
}

} //namespace impl
} //namespace api
} //namespace slack