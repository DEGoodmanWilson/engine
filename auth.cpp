//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/auth.h"
#include "private.h"
#include <string>
#include <cpr.h>
#include <iostream>

namespace slack
{

api_response auth::test() const
{
    cpr::Parameters params = {
            {"token", slack_config::token_}
    };

    auto result = cpr::Get(cpr::Url{"https://slack.com/api/auth.test"}, params);
    //TODO something more robust!
    return result.text;
}

} //namespace slack