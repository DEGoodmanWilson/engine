//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/base/event.h>
#include <slack/optional.hpp>
#include <vector>


namespace slack { namespace event
{


struct message : public base::event
{
    static const std::string type;

    //TODO how to deal with subtypes, _e.g_ message.channel_archive (which is not the same as channel_archive)
    // Would be nice to namespace them somehow! What's the right way to do this.
    // We can create a message namespace, but then how do we name the message class
    // Is message a base class of the others? And if so, how can we namespace them cleanly?

    // What I am going to try is this, and although it is a bit ugly, I just can't imagine the right way forward:
    //   slack::event::channel_archive (class)
    //   slack::event::message (class)
    //   slack::event::message_subtype (namespace)
    //   slack::event::message_subtype::channel_archive (class, inherits from event, not from message)
    //
    // I consider this pretty ugly. And perhaps I'll figure out an alternative. In the meantime, this will keep me coding.

    message() = default;

    template<class json>
    message(const json &parsed_json);

    //TODO we should implement these.
//    template<class json>
//    message(json &&parsed_json);

    slack::channel_id channel;
    slack::user_id user;
    std::string text;
    slack::ts ts;

    bool is_starred;
    std::vector<channel_id> pinned_to;
    std::vector<reaction> reactions;
};


}} //namespace event slack