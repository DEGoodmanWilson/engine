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
#include <optional/optional.hpp>

namespace slack
{
namespace channels
{

/*************************************************************/
// MARK: - Parameters

namespace parameter
{
namespace create
{

MAKE_BOOL_LIKE(exclude_archived);

} //namespace create
} //namespace parameter

/*************************************************************/
// MARK: - Response Errors

namespace response
{
namespace error
{
namespace create
{

const auto NAME_TAKEN = std::string{"name_taken"};
const auto RESTRICTED_ACTION = std::string{"restricted_action"};
const auto NO_CHANNEL = std::string{"no_channel"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};
const auto USER_IS_BOT = std::string{"user_is_bot"};
const auto USER_IS_RESTRICTED = std::string{"user_is_restricted"};

} //namespace create
} //namespace error
} //namespace response


/*************************************************************/
// MARK: - Response

namespace response
{

struct create :
        public slack::base::response
{
    create(const std::string &raw_json);

    std::experimental::optional<channel> channel;
};

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

class create :
        public slack::base::impl<response::create>
{
public:
    create(const std::string& name);
    //TODO can these be moved into the base class?
    response::create get_response();

private:
    std::string name_;
};

} //namespace impl


/*************************************************************/
// MARK: - Public Interface


response::create create(const std::string& name);


} //namespace channels
} //namespace slack