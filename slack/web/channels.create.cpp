//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/web/channels.create.h"
#include "private.h"

namespace slack { namespace channels
{

const auto NAME_TAKEN = std::string{"name_taken"};
const auto RESTRICTED_ACTION = std::string{"restricted_action"};
const auto NO_CHANNEL = std::string{"no_channel"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};
const auto USER_IS_BOT = std::string{"user_is_bot"};
const auto USER_IS_RESTRICTED = std::string{"user_is_restricted"};


create::create(const std::string &name)
        : name_{name}
{ }


void create::initialize_()
{
    http::params params{{"name", name_}};

    auto result_ob = slack_private::get(this, "channels.create", params);
    if (!this->error_message)
    {
        if (result_ob["channel"].isObject()) channel = slack::channel{result_ob["channel"]};
    }
}

}} //namespace channels slack