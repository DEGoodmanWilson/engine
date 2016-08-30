//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/base/event.h>
#include <slack/optional.hpp>


namespace slack { namespace event
{

struct user_typing : public base::event
{
    static const std::string type;

    user_typing() = default;

    template<class json>
    user_typing(const slack::team_id &team_id, const json &parsed_json);

    channel_id channel;
    user_id user;
};

}} //namespace event slack