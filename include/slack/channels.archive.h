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
namespace archive
{

} //namespace archive
} //namespace parameter

/*************************************************************/
// MARK: - Response Errors

namespace response
{
namespace error
{
namespace archive
{

const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
const auto CHANNEL_NOT_FOUND = std::string{"channel_not_found"};
const auto ALREADY_ARCHIVED = std::string{"already_archived"};
const auto CANT_ARCHIVE_GENERAL = std::string{"cant_archive_general"};
const auto LAST_RA_CHANNEL = std::string{"last_ra_channel"};
const auto RESTRICTED_ACTION = std::string{"restricted_action"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};
const auto USER_IS_BOT = std::string{"user_is_bot"};
const auto USER_IS_RESTRICTED = std::string{"user_is_restricted"};

} //namespace archive
} //namespace error
} //namespace response


/*************************************************************/
// MARK: - Response

namespace response
{

struct archive :
        public slack::base::response
{
    archive(const std::string &raw_json);
};

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

class archive :
        public slack::base::impl<response::archive>
{
public:
    archive(const channel_id& channel);
    //TODO can these be moved into the base class?
    response::archive get_response();

private:
    channel_id channel_;
};

} //namespace impl


/*************************************************************/
// MARK: - Public Interface


response::archive archive(const channel_id& channel);


} //namespace channels
} //namespace slack