//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <string>
#include <optional/optional.hpp>
#include <map>

namespace slack
{
namespace response
{

struct json_impl;

struct base
{
    base(const std::string &raw_json) : raw_json{raw_json} {}
    void parse(bool do_return = true);

    std::string raw_json;
    std::experimental::optional<std::string> error;

    operator bool()
    {
        return !static_cast<bool>(error); //if error contains a value, return false
    }

    virtual void finish_parse(json_impl* json) = 0;
};

}
}