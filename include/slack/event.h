//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/base/response.h>
#include <string>
#include <slack/optional.hpp>

namespace slack { namespace event
{

struct hello
{
};

struct user_typing
{
    user_typing() = default;
    template<class json>
    user_typing(const json &parsed_json);

    std::experimental::optional<channel_id> channel;
    std::experimental::optional<user_id> user;
};


}} //namespace events