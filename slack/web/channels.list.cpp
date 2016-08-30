//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/web/channels.list.h"
#include "private.h"
#include <json/json.h>

namespace slack { namespace channels
{

const std::string list::error::NOT_AUTHED = std::string{"not_authed"};
const std::string list::error::INVALID_AUTH = std::string{"invalid_auth"};
const std::string list::error::ACCOUNT_INACTIVE = std::string{"account_inactive"};

void list::initialize_()
{
    auto params = default_params({});

    if (exclude_archived_)
    {
        params.emplace("exclude_archived", (*exclude_archived_ ? "true" : "false"));
    }

    auto result_ob = slack_private::get(this, "channels.list", params);
    if (!this->error_message)
    {
        if (!result_ob["channels"].isNull() && result_ob["channels"].isArray())
        {
            channels = std::vector<channel>{};
            for (const auto channel_obj : result_ob["channels"])
            {
                channels->emplace_back(channel_obj);
            }
        }
    }
}

}} //namespace channels slack