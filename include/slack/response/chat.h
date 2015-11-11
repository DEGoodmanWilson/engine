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
namespace chat
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
    //TODO use more universal types here
    std::string channel;
    std::string ts;
};
}
}
}