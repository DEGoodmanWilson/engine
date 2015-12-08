//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <slack/base/impl.h>
#include <string>
#include <slack/optional.hpp>

namespace slack
{
namespace auth
{

class test : public slack::base::response2

{
public:
    // constructor
    test();

    // parameters
    struct parameter
    { };

    // errors
    struct error
    {
        static const std::string UNKNOWN; // = std::string{"unknown"};
        static const std::string JSON_PARSE_FAILURE; // = std::string{"json_parse_failure"};
        static const std::string INVALID_RESPONSE; // = std::string{"invalid_response"};
        static const std::string NOT_AUTHED; // = std::string{"not_authed"};
        static const std::string INVALID_AUTH; // = std::string{"invalid_auth"};
        static const std::string ACCOUNT_INACTIVE; // = std::string{"account_inactive"};
    };

    // response
    std::experimental::optional<std::string> url;
    std::experimental::optional<std::string> teamname;
    std::experimental::optional<std::string> username;
    std::experimental::optional<team_id> team_id;
    std::experimental::optional<user_id> user_id;

private:
};


} //namespace auth
} //namespace slack