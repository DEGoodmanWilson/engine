//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/response/base.h>
#include <string>

namespace slack
{

namespace chat
{

namespace responses
{

struct delete_it // : public ::slack::response::base
{
    delete_it(const std::string &raw_json) : raw_json{raw_json}, ok{false}, error{"unknown"}
    { }

    delete_it(const std::string &raw_json,
              bool ok,
              const std::experimental::optional<std::string> &error = std::experimental::nullopt) :
            raw_json{raw_json}, ok{ok}, error{error}
    { }

    delete_it(const std::string &raw_json,
              bool ok,
              const std::experimental::optional<std::string> &error,
              const std::string &channel,
              const std::string &ts) :
            raw_json{raw_json},
            ok{ok},
            error{error},
            channel{channel},
            ts{ts}
    { }

    explicit operator bool()
    {
        return ok;
    }

    std::string raw_json;
    bool ok;
    std::experimental::optional<std::string> error;
    channel_id channel;
    ts ts;
};

struct post_message // : public ::slack::response::base
{
    enum class error
    {
        unknown,
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

    post_message(const std::string &raw_json);

    post_message(const std::string &raw_json,
                 bool ok,
                 const std::experimental::optional<error> &error = std::experimental::nullopt) :
            raw_json{raw_json}, ok{ok}, error{error}
    { }

    post_message(const std::string &raw_json,
                 bool ok,
                 const std::experimental::optional<error> &error,
                 const ts &ts,
                 const channel_id &channel,
                 const message &message) :
            raw_json{raw_json},
            ok{ok},
            error{error},
            ts{ts},
            channel{channel},
            message{message}
    { }

    explicit operator bool()
    {
        return ok;
    }

    std::string raw_json;
    bool ok;
    std::experimental::optional<error> error;
    ts ts;
    channel_id channel;
    message message;
};

}
}
}