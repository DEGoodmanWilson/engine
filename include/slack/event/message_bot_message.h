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


struct message_bot_message : public base::event
{
    static const std::string event_name;

    message_bot_message() = default;

    template<class json>
    message_bot_message(const json &parsed_json);

    channel_id channel;
    bot_id bot_id;
    std::string username;
    std::string text;
    ts ts;
    std::vector<std::string> icons;

    bool is_starred;
    std::vector<channel_id> pinned_to;
    std::vector<reaction> reactions;
};


}} //namespace event slack