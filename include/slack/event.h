//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/base/event.h>
#include <slack/event/hello.h>
#include <slack/event/user_typing.h>

namespace slack { namespace event
{

template<class T>
std::shared_ptr<T> cast(std::shared_ptr<base::event> event)
{
    static_assert(std::is_base_of<base::event, T>::value, "Not a type derived from event");
    return std::dynamic_pointer_cast<T>(event);
}

}} //namespace event slack