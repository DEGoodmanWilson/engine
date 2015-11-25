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
namespace rtm
{
namespace response
{

namespace error
{
namespace start
{
const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
const auto MIGRATION_IN_PROGRESS = std::string{"migration_in_progress"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};
}
}

struct start :
        public slack::response::base
{
    start(const std::string &raw_json) : base{raw_json}
    { parse(); };

    void finish_parse(slack::response::json_impl *json) override final;

    std::experimental::optional<std::string> url;
    std::experimental::optional<user> self;
    std::experimental::optional<team> team;
    std::experimental::optional<std::vector<user>> users;
    std::experimental::optional<std::vector<channel>> channels;
    std::experimental::optional<std::vector<group>> groups;
    std::experimental::optional<std::vector<mpim>> mpims;
    std::experimental::optional<std::vector<im>> ims;
    std::experimental::optional<std::vector<bot>> bots;
};

} //namespace response
} //namespace rtm
} //namespace slack
