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

response::list list::get_response()
{
    cpr::Parameters params; //no need for a token here
    params.AddParameter({"token", slack_config::token_});

    if (exclude_archived_)
    {
        std::string val{"false"};
        if(*exclude_archived_) val = "true";
        params.AddParameter({"exclude_archived", val});
    }

    auto result = cpr::Get(cpr::Url{slack_config::HOSTNAME + "channels.list"}, params);
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