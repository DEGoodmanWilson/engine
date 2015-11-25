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
namespace archive
{
const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
const auto CHANNEL_NOT_FOUND = std::string{"channel_not_found"};
const auto ALREADY_ARCHIVED = std::string{"already_archived"};
const auto CANT_ARCHIVE_GENERAL = std::string{"cant_archive_general"};
const auto LAST_RA_CHANNEL = std::string{"last_ra_channel"};
const auto RESTRICTED_ACTION = std::string{"restricted_action"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};
const auto USER_IS_BOT = std::string{"user_is_bot"};
const auto USER_IS_RESTRICTED = std::string{"user_is_restricted"};
}
}


struct archive :
        public slack::response::base
{
    archive(const std::string &raw_json) : slack::response::base{raw_json}
    { parse(); }

    void finish_parse(slack::response::json_impl *json) override final;
};

} //namespace response
} //namespace channels
} //namespace slack