//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <slack/auth.h>
#include <cpr.h>

extern std::string slack_config::token_;

namespace slack
{

namespace auth
{


api_response test_wrapper::get_response()
{
    cpr::Parameters params; //no need for a token here
    params.AddParameter({"token", slack_config::token_});

    auto result = cpr::Get(cpr::Url{slack_config::HOSTNAME + "auth.test"}, params);
    return result.text;
}

api_response test()
{
    test_wrapper wrapper;
    return wrapper.get_response();
}

} //namespace auth
} //namespace slack
