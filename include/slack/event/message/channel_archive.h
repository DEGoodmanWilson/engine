//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/event.h>
#include <slack/base/event.h>
#include <slack/optional.hpp>
#include <vector>


namespace slack { namespace event { namespace message_subtype
{


struct channel_archive : public base::event
{
    static const std::string event_name;

    channel_archive() = default;

    template<class json>
    channel_archive(const json &parsed_json);

    std::experimental::optional<user_id> user;
    std::experimental::optional<std::string> text;
    std::experimental::optional<ts> ts;
    std::experimental::optional<std::vector<user_id>> members;
};


}}} //namespace message_subtype event slack