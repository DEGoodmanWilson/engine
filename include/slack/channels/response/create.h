//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/response/base.h>
#include <slack/types.h>
#include <string>
#include <vector>
#include <optional/optional.hpp>

namespace slack
{
namespace channels
{
namespace response
{

namespace error
{
namespace create
{
const auto NAME_TAKEN = std::string{"name_taken"};
const auto RESTRICTED_ACTION = std::string{"restricted_action"};
const auto NO_CHANNEL = std::string{"no_channel"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};
const auto USER_IS_BOT = std::string{"user_is_bot"};
const auto USER_IS_RESTRICTED = std::string{"user_is_restricted"};
}
}


struct create :
        public slack::response::base
{
    create(const std::string &raw_json) : slack::response::base{raw_json}
    { parse(); }

    void finish_parse(slack::response::json_impl *json) override final;

    std::experimental::optional<channel> channel;
};

} //namespace response
} //namespace channels
} //namespace slack