//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/response/base.h>
#include <string>

namespace slack
{
namespace response
{
namespace auth
{

struct test // : public ::slack::response::base
{
    test(const std::string &raw_json) : raw_json{raw_json}, ok{false}, error{"unknown"}
    { }

    test(const std::string &raw_json,
         bool ok,
         const std::experimental::optional<std::string> &error = std::experimental::nullopt) :
            raw_json{raw_json}, ok{ok}, error{error}
    { }

    test(const std::string &raw_json,
         bool ok,
         const std::experimental::optional<std::string> &error,
         const std::string &url,
         const std::string &team,
         const std::string &user,
         const slack::team_id &team_id,
         const slack::user_id &user_id) :
            raw_json{raw_json},
            ok{ok},
            error{error},
            url{url},
            team{team},
            user{user},
            team_id{team_id},
            user_id{user_id}
    { }

    explicit operator bool()
    {
        return ok;
    }

    std::string raw_json;
    bool ok;
    std::experimental::optional<std::string> error;
    std::string url;
    std::string team;
    std::string user;
    ::slack::team_id team_id;
    ::slack::user_id user_id;
};
}
}
}