//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/base/event.h>
#include <slack/optional.hpp>
#include <iostream>


namespace slack { namespace event
{


struct hello :
        public base::event
{
    static const std::string type;

    hello() = default;

    template<class json>
    hello(const slack::team_id &team_id, const json &parsed_json) : event{team_id, parsed_json}
    {}
};


}} //namespace event slack