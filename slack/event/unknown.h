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


struct unknown :
        public base::event
{
    std::string type; //this one isn't static, because it will hold new events we don't recognize

    unknown() = default;

    template<class json>
    unknown(const slack::team_id &team_id, const json &parsed_json);
};


}} //namespace event slack