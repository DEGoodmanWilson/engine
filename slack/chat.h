//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <string>
#include <slack/impl/private.h>
#include <slack/impl/chat__post_message.h>

namespace engine
{
namespace endpoints
{
class chat
{
public:
    using message = int;

    template<typename ...Os>
    message postMessage(const channel_id &channel, const std::string &text)
    {
        chat__post_message_ session; //{channel, text};
        return session.execute();
    }

    template<typename ...Os>
    message postMessage(const channel_id &channel, const std::string &text, Os &&...os)
    {
        chat__post_message_ session; //{channel, text};
        private_::set_option<decltype(session)>(session, SLACK_FWD(os)...);
        return session.execute();
    }
};
} //namespace endpoints
} //namespace engine