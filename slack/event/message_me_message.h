//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/base/event.h>
#include <slack/optional.hpp>
#include <vector>


namespace slack { namespace event
{


struct message_me_message : public base::event
{
    static const std::string type;

    virtual std::string str()
    {
        return type;
    }

    message_me_message() = default;

    template<class json>
    message_me_message(const slack::team_id &team_id, const json &parsed_json);

    slack::channel_id channel;
    slack::user_id user;
    std::string text;
    slack::ts ts;

    bool is_starred;
    std::vector<slack::channel_id> pinned_to;
    std::vector<slack::reaction> reactions;
};


}} //namespace event slack