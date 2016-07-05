//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/web/channels.rename.h"
#include "private.h"

namespace slack { namespace channels
{

const auto CHANNEL_NOT_FOUND = std::string{"channel_not_found"};
const auto NOT_IN_CHANNEL = std::string{"not_in_channel"};
const auto NOT_AUTHORIZED = std::string{"not_authorized"};
const auto INVALID_NAME = std::string{"invalid_name"};
const auto NAME_TAKEN = std::string{"name_taken"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};
const auto USER_IS_BOT = std::string{"user_is_bot"};
const auto USER_IS_RESTRICTED = std::string{"user_is_restricted"};

void rename::initialize_()
{
    auto params = default_params({
            {"channel", channel_},
            {"name",    name_}
    });

    auto result_ob = slack_private::get(this, "channels.rename", params);

    if (!this->error_message)
    {
        if (result_ob["channel"].isObject()) channel = slack::channel{result_ob["channel"]};
    }
}

}} //namespace channels slack