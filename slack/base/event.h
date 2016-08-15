//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <memory>
#include <functional>
#include <optional.hpp>

namespace slack { namespace base
{

struct event
{
    //This space left intentionally blank
    event() = default;
    virtual ~event() = default;

    template<class json>
    event(const json &parsed_json);

    std::experimental::optional<std::string> token; //tokens only come through events API
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