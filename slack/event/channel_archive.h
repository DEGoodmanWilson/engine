//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/event.h>
#include <slack/base/event.h>
#include <slack/optional.hpp>
#include <vector>


namespace slack { namespace event
{


struct channel_archive : public base::event
{
    static const std::string type;

    channel_archive() = default;

    template<class json>
    channel_archive(const json &parsed_json);

    std::experimental::optional<channel_id> channel;
    std::experimental::optional<user_id> user;
};


}} //namespace event slack