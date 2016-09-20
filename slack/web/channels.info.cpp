//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/web/channels.info.h"
#include "private.h"

namespace slack { namespace channels
{

const auto CHANNEL_NOT_FOUND = std::string{"channel_not_found"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};

void info::initialize_()
{
    auto params = default_params({
                                         {"channel", channel_}
                                 });

    auto result_ob = slack_private::get(this, "channels.info", params);

    if (!this->error_message)
    {
        if (result_ob["channel"].isObject()) channel = slack::channel{result_ob["channel"]};
    }
}

}} //namespace channels slack