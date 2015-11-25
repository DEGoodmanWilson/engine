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
namespace list
{
const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};
}
}


struct list : public slack::response::base
{
    list(const std::string &raw_json) : slack::response::base{raw_json}
    { parse(); }

    void finish_parse(slack::response::json_impl *json) override final;

    std::experimental::optional<std::vector<::slack::channel>> channels;
};

} //namespace response
} //namespace channels
} //namespace slack