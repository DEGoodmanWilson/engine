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

namespace slack { namespace auth
{

class test :
        public slack::base::response
{
public:
    // constructor
    test();

    // parameters
    struct parameter
    {
    };

    // errors
    struct error
    {
        static const std::string NOT_AUTHED;
        static const std::string INVALID_AUTH;
        static const std::string ACCOUNT_INACTIVE;
    };

    // response
    std::experimental::optional<std::string> url;
    std::experimental::optional<std::string> teamname;
    std::experimental::optional<std::string> username;
    std::experimental::optional<team_id> team_id;
    std::experimental::optional<user_id> user_id;

private:
};

}} //namespace auth slack