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

struct delete_it
{
    delete_it(const std::string &raw_json);

    explicit operator bool()
    {
        return ok;
    }

    enum class error
    {
        unknown,
        json_parse_failure,
        invalid_response,
        message_not_found,
        channel_not_found,
        cant_delete_message,
        compliance_exports_prevent_deletion,
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
    channel_id channel;
    ts ts;
};

} //namespace response
} //namespace chat
} //namespace slack