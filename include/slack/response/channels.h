//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/response/base.h>
#include <string>
#include <vector>
#include <optional/optional.hpp>

namespace slack
{
namespace response
{
namespace channels
{

struct list // : public ::slack::response::base
{
    list(const std::string &raw_json);

    explicit operator bool()
    {
        return ok;
    }

    std::string raw_json;
    bool ok;
    std::experimental::optional<std::string> error;

    std::vector<::slack::channel> channels;
};

}

}

}