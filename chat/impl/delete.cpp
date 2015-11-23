//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/chat.h"
#include "config.h"
#include <cpr.h>
#include <json/json.h>

namespace slack_config
{
extern std::string token_;
}

namespace slack
{
namespace chat
{
namespace impl
{

response::delete_it delete_it::get_response()
{
    cpr::Parameters params;
    params.AddParameter({"token", slack_config::token_});

    auto result = cpr::Get(cpr::Url{slack_config::HOSTNAME + "chat.delete"}, params);
    if (result.status_code != 200)
    {
        //error path
        return {result.text}; //TODO
    }

    return {result.text};
}


} //namespace impl
} //namespace chat
} //namespace slack
