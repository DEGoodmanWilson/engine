//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "auth.h"
#include <string>
#include <cpr.h>
#include <iostream>

namespace slack_config
{
    extern std::string token_;
}
namespace slack
{

std::string auth::test()
{
    cpr::Parameters params = {
            {"token", slack_config::token_}
    };

    auto result = cpr::Get(cpr::Url{"https://slack.com/api/auth.test"}, params);
    //TODO something more robust!
    return result.text;
}

} //namespace slack