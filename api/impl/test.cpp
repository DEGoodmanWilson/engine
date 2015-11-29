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

response::test test::get_response()
{
    cpr::Parameters params; //no need for a token here
    if (error_)
    {
        params.AddParameter({"error", *error_});
    }
    if (foo_)
    {
        params.AddParameter({"foo", *foo_});
    }

    auto result = cpr::Get(cpr::Url{slack_config::HOSTNAME + "api.test"}, params);

    return handle_response(result.status_code, result.text);
}

} //namespace impl
} //namespace api
} //namespace slack
