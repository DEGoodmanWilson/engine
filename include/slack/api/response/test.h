//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/response/base.h>
#include <map>

namespace slack
{
namespace api
{
namespace response
{

namespace error
{
const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
}

struct test :
        public slack::response::base
{
    test(const std::string &raw_json) : slack::response::base{raw_json}
    { parse(false); }

    void finish_parse(slack::response::json_impl *json) override final;

    std::experimental::optional<std::map<std::string, std::string>> args;
};

} //namespace response
} //namespace api
} //namespace slack