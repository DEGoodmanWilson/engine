//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/web/oauth.access.h"
#include "private.h"
#include <vector>
#include <sstream>
#include <iostream>

namespace slack { namespace oauth
{

const std::string access::error::INVALID_CLIENT_ID = std::string{"invalid_client_id"};
const std::string access::error::BAD_CLIENT_SECRET = std::string{"bad_client_secret"};
const std::string access::error::INVALID_CODE = std::string{"invalid_code"};
const std::string access::error::BAD_REDIRECT_URI = std::string{"bad_redirect_uri"};

void access::initialize_()
{
    auto params = default_params({
                                         {"client_id",     client_id_},
                                         {"client_secret", client_secret_},
                                         {"code",          code_}
                                 });

    if (redirect_uri_)
    {
        params.emplace("redirect_uri", *redirect_uri_);
    }

    auto result_ob = slack_private::get(this, "oauth.access", params);
    if(this->success())
    {
        if (result_ob["access_token"].isString()) access_token = {result_ob["access_token"].asString()};
        if (result_ob["scope"].isString())
        {
            std::string s;
            std::istringstream f{result_ob["scope"].asString()};
            while (std::getline(f, s, ','))
            {
                scope.push_back(s);
            }
        }
        if (result_ob["user_id"].isString()) user_id = {result_ob["user_id"].asString()};
        if (result_ob["team_name"].isString()) team_name = {result_ob["team_name"].asString()};
        if (result_ob["team_id"].isString()) team_id = {result_ob["team_id"].asString()};

        if (result_ob["bot"].isObject())
        {
            bot = bot_info{result_ob["bot"]["bot_user_id"].asString(), result_ob["bot"]["bot_access_token"].asString()};
        }
    }
}

}} //namespace oauth slack