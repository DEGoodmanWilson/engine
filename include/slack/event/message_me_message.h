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


struct message_me_message : public base::event
{
    static const std::string event_name;

    message_me_message() = default;

    template<class json>
    message_me_message(const json &parsed_json);

    channel_id channel;
    user_id user;
    std::string text;
    ts ts;

    bool is_starred;
    std::vector<channel_id> pinned_to;
    std::vector<reaction> reactions;
};


}} //namespace event slack