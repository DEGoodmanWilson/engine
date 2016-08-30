//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/web/auth.test.h"
#include "private.h"

namespace slack { namespace auth
{

const std::string test::error::NOT_AUTHED = std::string{"not_authed"};
const std::string test::error::INVALID_AUTH = std::string{"invalid_auth"};
const std::string test::error::ACCOUNT_INACTIVE = std::string{"account_inactive"};


void test::initialize_()
{
    auto params = default_params({ });

    auto result_ob = slack_private::get(this, "auth.test", params);
    if (!this->error_message)
    {
        if (result_ob["url"].isString()) url = result_ob["url"].asString();
        if (result_ob["team"].isString()) teamname = result_ob["team"].asString();
        if (result_ob["user"].isString()) username = result_ob["user"].asString();
        if (result_ob["team_id"].isString()) team_id = slack::team_id{result_ob["team_id"].asString()};
        if (result_ob["user_id"].isString()) user_id = slack::user_id{result_ob["user_id"].asString()};
    }
}

}} //namespace auth slack