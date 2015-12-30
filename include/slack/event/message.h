//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/event.h>
#include <slack/base/event.h>
#include <slack/optional.hpp>
#include <vector>


namespace slack { namespace event
{


struct message : public base::event
{
    static const std::string event_name;

    //TODO how to deal with subtypes, _e.g_ message.channel_archive (which is not the same as channel_archive)
    // Would be nice to namespace them somehow! What's the right way to do this.
    // We can create a message namespace, but then how do we name the message class
    // Is message a base class of the others? And if so, how can we namespace them cleanly?

    message() = default;

    template<class json>
    message(const json &parsed_json);

    std::experimental::optional<channel_id> channel;
    std::experimental::optional<user_id> user;
    std::experimental::optional<std::string> text;
    std::experimental::optional<ts> ts;
    std::experimental::optional<bool> hidden;

    std::experimental::optional<bool> is_starred;
    std::experimental::optional<std::vector<channel_id>> pinned_to;
    std::experimental::optional<std::vector<reaction>> reactions;
};


}} //namespace event slack