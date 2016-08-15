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


struct message_channel_archive : public base::event
{
    static const std::string type;

    message_channel_archive() = default;

    template<class json>
    message_channel_archive(const json &parsed_json);

    slack::user_id user;
    std::string text;
    slack::ts ts;
    std::vector<user_id> members;
};


}} //namespace event slack