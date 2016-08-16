//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <memory>
#include <functional>
#include <slack/optional.hpp>

namespace slack { namespace base
{

struct event
{
    //This space left intentionally blank
    event() = default;
    virtual ~event() = default;

    template<class json>
    event(const json &parsed_json) {};
};

}} //namespace base slack