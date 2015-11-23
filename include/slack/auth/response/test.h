//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <string>
#include <map>
#include <optional/optional.hpp>

namespace slack
{
namespace auth
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
        not_authed,
        invalid_auth,
        account_inactive,
    };

    static const std::map<std::string, error> error_str_map;

    //common stuff
    std::string raw_json;
    bool ok;
    std::experimental::optional<error> error;
    std::experimental::optional<std::string> error_str;

    std::experimental::optional<std::string> url;
    std::experimental::optional<std::string> teamname;
    std::experimental::optional<std::string> username;
    std::experimental::optional<team_id> team_id;
    std::experimental::optional<user_id> user_id;
};

} //namepsace response
} //namespace auth
} //namespace slack