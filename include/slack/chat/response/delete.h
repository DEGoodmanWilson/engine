//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/response/base.h>
#include <slack/types.h>
#include <string>
#include <optional/optional.hpp>

namespace slack
{
namespace chat
{
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
}
}

struct delete_it :
        public slack::response::base
{
    delete_it(const std::string &raw_json) : base{raw_json}
    { parse(); };

    void finish_parse(slack::response::json_impl *json) override final;

    channel_id channel;
    ts ts;
};

} //namespace response
} //namespace chat
} //namespace slack