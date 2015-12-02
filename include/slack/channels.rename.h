//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <slack/base/impl.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>

namespace slack
{
namespace channels
{

/*************************************************************/
// MARK: - Parameters

namespace parameter
{
namespace rename
{

MAKE_BOOL_LIKE(exclude_archived);

} //namespace rename
} //namespace parameter

/*************************************************************/
// MARK: - Response Errors

namespace response
{
namespace error
{
namespace rename
{

const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
const auto CHANNEL_NOT_FOUND = std::string{"channel_not_found"};
const auto NOT_IN_CHANNEL = std::string{"not_in_channel"} ;
const auto NOT_AUTHORIZED = std::string{"not_authorized"} ;
const auto INVALID_NAME = std::string{"invalid_name"} ;
const auto NAME_TAKEN = std::string{"name_taken"} ;
const auto NOT_AUTHED = std::string{"not_authed"} ;
const auto INVALID_AUTH = std::string{"invalid_auth"} ;
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"} ;
const auto USER_IS_BOT = std::string{"user_is_bot"};
const auto USER_IS_RESTRICTED = std::string{"user_is_restricted"};


} //namespace rename
} //namespace error
} //namespace response


/*************************************************************/
// MARK: - Response

namespace response
{

struct rename :
        public slack::base::response
{
    rename(const std::string &raw_json);

    std::experimental::optional<channel> channel;
};

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

class rename :
        public slack::base::impl<response::rename>
{
public:
    rename(const channel_id& channel, const std::string& name);
    //TODO can these be moved into the base class?
    response::rename get_response();

private:
    channel_id channel_;
    std::string name_;
};

} //namespace impl


/*************************************************************/
// MARK: - Public Interface


response::rename rename(const channel_id& channel, const std::string& name);


} //namespace channels
} //namespace slack