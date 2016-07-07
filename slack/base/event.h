//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <memory>
#include <functional>

namespace slack { namespace base
{

struct event
{
    //This space left intentionally blank
    event() = default;
    virtual ~event() = default;
};

/***
 * Adapted from http://www.gamedev.net/page/resources/_/technical/game-programming/effective-event-handling-in-c-r2459
 */

class event_handler_callback
{
public:
    virtual ~event_handler_callback() = default;
    void exec(std::shared_ptr<slack::base::event> event) {call(event);}

private:
    virtual void call(std::shared_ptr<slack::base::event>) = 0;
};




}} //namespace base slack