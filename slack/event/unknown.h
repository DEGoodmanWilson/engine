//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/event.h>
#include <slack/base/event.h>
#include <slack/optional.hpp>


namespace slack { namespace event
{


struct unknown :
        public base::event
{
    unknown(const std::string& name) : name{name} {}
    unknown(std::string&& name) : name{std::move(name)} {}

    const std::string name; //this one isn't static, because it will hold new events we don't recognize
};


}} //namespace event slack