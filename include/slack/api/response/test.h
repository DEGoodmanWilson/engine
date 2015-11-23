//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <map>
#include <slack/response/base.h>

namespace slack
{
namespace api
{
namespace response
{

struct test
{
    test(const std::string &raw_json);

    explicit operator bool()
    {
        return ok;
    }

    enum class error
    {
        unknown,
        json_parse_failure,
        invalid_response,
        user_specified,
    };

    //common stuff
    std::string raw_json;
    bool ok;
    std::experimental::optional<error> error;
    std::experimental::optional<std::string> error_str;

    //specific stuff
    std::experimental::optional<std::multimap<std::string, std::string>> args;
};

} //namespace response
} //namespace api
} //namespace slack