//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/web/users.info.h"
#include "private.h"

namespace slack { namespace users
{

const std::string info::error::USER_NOT_FOUND = std::string{"user_not_found"};
const std::string info::error::USER_NOT_VISIBLE = std::string{"user_not_visible"};
const std::string info::error::NOT_AUTHED = std::string{"not_authed"};
const std::string info::error::INVALID_AUTH = std::string{"invalid_auth"};
const std::string info::error::ACCOUNT_INACTIVE = std::string{"account_inactive"};


void info::initialize_()
{
    auto params = default_params({
            {"user", user_},
    });

    auto result_ob = slack_private::get(this, "users.info", params);

    if (!this->error_message)
    {
        if (result_ob["user"].isObject()) user = slack::user{result_ob["user"]};
    }
}

}} //namespace users slack