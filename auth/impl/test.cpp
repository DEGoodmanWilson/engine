//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/auth.h"
#include "config.h"
#include <cpr.h>
#include <json/json.h>

namespace slack_config
{
extern std::string token_;
}

namespace slack
{
namespace auth
{
namespace impl
{

response::test test::get_response()
{
    cpr::Parameters params; //no need for a token here
    params.AddParameter({"token", slack_config::token_});

    auto result = cpr::Get(cpr::Url{slack_config::HOSTNAME + "auth.test"}, params);
    if (result.status_code != 200)
    {
        //error path
        return {result.text}; //TODO
    }
    
    return {result.text};
}


} //namespace impl
} //namespace auth
} //namespace slack
