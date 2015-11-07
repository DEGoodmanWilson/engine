//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <slack/api.h>
#include "private.h"
#include <string>
#include <cpr.h>
#include <iostream>



namespace slack
{

api_response api::test(const std::string &error, const std::string &foo) const
{
    cpr::Parameters params;
    if(!error.empty())
        params.AddParameter({"error", error});
    if(!foo.empty())
        params.AddParameter({"foo", foo});

    auto result = cpr::Get(cpr::Url{"https://slack.com/api/api.test"}, params);
    //TODO something more robust!
    return result.text;
}

} //namespace slack