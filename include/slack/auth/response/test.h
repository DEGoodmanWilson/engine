//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/response/base.h>
#include <slack/types.h>
#include <string>
#include <optional/optional.hpp>

namespace slack
{
namespace auth
{
namespace response
{

namespace error
{
namespace test
{
const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};
}
}

struct test :
        public slack::response::base
{
    test(const std::string &raw_json) : slack::response::base{raw_json}
    { parse(); }

    void finish_parse(slack::response::json_impl *json) override final;

    std::experimental::optional<std::string> url;
    std::experimental::optional<std::string> teamname;
    std::experimental::optional<std::string> username;
    std::experimental::optional<team_id> team_id;
    std::experimental::optional<user_id> user_id;
};

} //namepsace response
} //namespace auth
} //namespace slack