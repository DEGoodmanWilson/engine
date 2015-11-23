//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/response/base.h>
#include <slack/types.h>

namespace slack
{
namespace chat
{
namespace response
{

struct post_message
{
    post_message(const std::string &raw_json);

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
        channel_not_found,
        not_in_channel,
        is_archived,
        msg_too_long,
        no_text,
        rate_limited,
        not_authed,
        invalid_auth,
        account_inactive,
    };

    //common stuff
    static const std::map<std::string, error> error_str_map;
    std::string raw_json;
    bool ok;
    std::experimental::optional<error> error;
    std::experimental::optional<std::string> error_str;

    //specific stuff
    ::slack::ts ts;
    ::slack::channel_id channel;
    ::slack::message message;
};

} //namespace response
} //namespace chat
} //namespace slack