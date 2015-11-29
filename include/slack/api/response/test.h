//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/base/response.h>
#include <map>

namespace slack
{
namespace api
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
}
}

struct test :
        public slack::base::response
{
    test(const std::string &raw_json);

    std::experimental::optional<std::map<std::string, std::string>> args;
};

} //namespace response
} //namespace api
} //namespace slack