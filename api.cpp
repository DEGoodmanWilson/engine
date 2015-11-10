//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <slack/api.h>
#include <cpr.h>

namespace slack
{

namespace api
{


api_response test_wrapper::get_response()
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
    return result.text;
}
} //namespace api
} //namespace slack
