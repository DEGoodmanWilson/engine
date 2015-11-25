//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/channels.h"
#include "config.h"
#include <cpr.h>
#include <json/json.h>

namespace slack_config
{
extern std::string token_;
}

namespace slack
{
namespace channels
{
namespace impl
{

response::archive archive::get_response()
{
    cpr::Parameters params{
            {"token", slack_config::token_},
            {"channel", channel_}
    };

    auto result = cpr::Get(cpr::Url{slack_config::HOSTNAME + "channels.archive"}, params);
    if (result.status_code != 200)
    {
        //error path
        return {result.text}; //TODO
    }

    return {result.text};
}

} //namespace impl
} //namespace channels
} //namespace slack