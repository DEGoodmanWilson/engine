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

/*************************************************************/
// MARK: - Parameters

namespace parameter
{
namespace test
{

//no optional parameters

} //namespace test
} //namespace parameter

/*************************************************************/
// MARK: - Response Errors

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

} //namespace test
} //namespace error
} //namespace response


/*************************************************************/
// MARK: - Response

namespace response
{

struct test :
        public slack::base::response
{
    test(const std::string &raw_json);

    std::experimental::optional<std::string> url;
    std::experimental::optional<std::string> teamname;
    std::experimental::optional<std::string> username;
    std::experimental::optional<team_id> team_id;
    std::experimental::optional<user_id> user_id;
};

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

class test :
        public slack::base::impl<response::test>
{
public:
    response::test get_response();

private:

};

} //namespace impl


/*************************************************************/
// MARK: - Public Interface


response::test test();

} //namespace auth
} //namespace slack