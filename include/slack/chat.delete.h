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
namespace chat
{

/*************************************************************/
// MARK: - Parameters

namespace parameter
{
namespace delete_it
{

//no optional parameters

} //namespace delete_it
} //namespace parameter

/*************************************************************/
// MARK: - Response Errors

namespace response
{
namespace error
{
namespace delete_it
{

const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
const auto MESSAGE_NOT_FOUND = std::string{"message_not_found"};
const auto CHANNEL_NOT_FOUND = std::string{"channel_not_found"};
const auto CANT_DELETE_MESSAGE = std::string{"cant_delete_message"};
const auto COMPLIANCE_EXPORTS_PREVENT_DELETION = std::string{"compliance_exports_prevent_deletion"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};

} //namespace delete_it
} //namespace error
} //namespace response


/*************************************************************/
// MARK: - Response

namespace response
{

struct delete_it :
        public slack::base::response
{
    delete_it(const std::string &raw_json);

    std::experimental::optional<channel_id> channel;
    std::experimental::optional<ts> ts;
};

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

class delete_it :
        public slack::base::impl<response::delete_it>
{
public:
    delete_it(const ts &ts, const channel_id &channel);

    //TODO can these be moved into the base class?
    response::delete_it get_response();

private:
    ts ts_;
    channel_id channel_;
};

} //namespace impl


/*************************************************************/
// MARK: - Public Interface


response::delete_it delete_it(const ts &ts, const channel_id &channel);


} //namespace chat
} //namespace slack