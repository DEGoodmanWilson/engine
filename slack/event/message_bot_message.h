//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/base/event.h>
#include <slack/optional.hpp>
#include <vector>


namespace slack { namespace event
{


struct message_bot_message : public base::event
{
    static const std::string type;

    message_bot_message() = default;

    template<class json>
    message_bot_message(const json &parsed_json);

    slack::channel_id channel;
    slack::bot_id bot_id;
    std::string username;
    std::string text;
    slack::ts ts;
    std::vector<std::string> icons;

    bool is_starred;
    std::vector<slack::channel_id> pinned_to;
    std::vector<slack::reaction> reactions;
};


}} //namespace event slack