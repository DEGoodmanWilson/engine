//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/base/event.h>
#include <slack/optional.hpp>


namespace slack { namespace event
{

struct pong : public base::event
{
    static const std::string type;

    pong() = default;

    template<class json>
    pong(const json &parsed_json);

    std::string reply_to;
    std::string time;
};

}} //namespace event slack