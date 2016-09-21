//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
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

    virtual std::string str()
    {
        return type;
    }

    hello() = default;

    template<class json>
    hello(const slack::team_id &team_id, const json &parsed_json) : event{team_id, parsed_json}
    {}
};


}} //namespace event slack