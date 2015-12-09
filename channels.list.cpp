//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/channels.list.h"
#include "slack/http.h"
#include "private.h"
#include <json/json.h>

namespace slack { namespace channels
{

const std::string list::error::NOT_AUTHED = std::string{"not_authed"};
const std::string list::error::INVALID_AUTH = std::string{"invalid_auth"};
const std::string list::error::ACCOUNT_INACTIVE = std::string{"account_inactive"};

void list::initialize_()
{
    http::params params;

    if (exclude_archived_)
    {
        params.emplace("exclude_archived", (*exclude_archived_ ? "true" : "false"));
    }

    auto result_ob = slack_private::get(this, "channels.list", params);
    if (!this->error_message)
    {
        if (!result_ob["channels"].isNull() && result_ob["channels"].isArray())
        {
            channels = std::vector<::slack::channel>{};
            for (const auto channel_obj : result_ob["channels"])
            {
                channels->emplace_back(channel_obj);
            }
        }
    }
}

}} //namespace channels slack