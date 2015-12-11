//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/rtm.start.h"
#include "private.h"

namespace slack { namespace rtm
{

const auto MIGRATION_IN_PROGRESS = std::string{"migration_in_progress"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};


void start::initialize_()
{
    http::params params;

    //optional parameters
    if (simple_latest_)
    {
        params.emplace("simple_latest", (*simple_latest_ ? "true" : "false"));
    }
    if (no_unreads_)
    {
        params.emplace("no_unreads", (*no_unreads_ ? "true" : "false"));
    }
    if (mpim_aware_)
    {
        params.emplace("mpim_aware", (*mpim_aware_ ? "true" : "false"));
    }

    auto result_ob = slack_private::get(this, "rtm.start", params);

    if (!this->error_message)
    {
        if (result_ob["url"].isString()) url = result_ob["url"].asString();

        if (!result_ob["channels"].isNull() && result_ob["channels"].isArray())
        {
            channels = std::vector<::slack::channel>{};
            for (const auto channel_obj : result_ob["channels"])
            {
                channels->emplace_back(channel_obj);
            }
        }

        //TODO: There is a lot of work left to be done here!
    }
}

}} //namespace rtm slack