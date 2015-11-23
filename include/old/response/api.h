//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/response/base.h>
#include <string>
#include <map>
#include <optional/optional.hpp>

namespace slack
{
namespace response
{
namespace api
{

struct test // : public ::slack::response::base
{
    test(const std::string &raw_json) : raw_json{raw_json}, ok{false}, error{"unknown"}
    { }

    test(const std::string &raw_json,
         bool ok,
         const std::experimental::optional<std::multimap<std::string, std::string>> &args,
         const std::experimental::optional<std::string> &error) :
            raw_json{raw_json}, args{args}, error{error}
    { }

    explicit operator bool()
    {
        return ok;
    }

    std::string raw_json;
    bool ok;
    std::experimental::optional<std::multimap<std::string, std::string>> args;
    std::experimental::optional<std::string> error;
};

}

}

}