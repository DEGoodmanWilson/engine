//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/rtm.h"
#include "config.h"
#include <cpr.h>
#include <json/json.h>

namespace slack_config
{
extern std::string token_;
}

namespace slack
{
namespace rtm
{
namespace impl
{

response::start start::get_response()
{
    cpr::Parameters params{
            {"token", slack_config::token_}
    };

    //optional parameters

    if (simple_latest_)
    {
        std::string val{static_cast<bool>(*simple_latest_) ? "true" : "false"};
        params.AddParameter({"simple_latest", val});
    }
    if (no_unreads_)
    {
        std::string val{static_cast<bool>(*no_unreads_) ? "true" : "false"};
        params.AddParameter({"no_unreads", val});
    }
    if (mpim_aware_)
    {
        std::string val{static_cast<bool>(*mpim_aware_) ? "true" : "false"};
        params.AddParameter({"mpim_aware", val});
    }

    auto result = cpr::Get(cpr::Url{slack_config::HOSTNAME + "rtm.start"}, params);
    if (result.status_code != 200)
    {
        //error path
        return {result.text}; //TODO
    }

    return {result.text};
}


} //namespace impl
} //namespace rtm
} //namespace slack
