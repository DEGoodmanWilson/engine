//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <string>
#include <slack/set_option.h>
#include <slack/chat.postMessage.h>

namespace slack
{
namespace containers
{
class chat
{
public:
    using message = int;

    template<typename ...Os>
    message postMessage(const channel_id &channel, const std::string &text)
    {
        return std::unique_ptr<chat::post_message>(channel, text);
    }

    template<typename ...Os>
    message postMessage(const channel_id &channel, const std::string &text, Os &&...os)
    {
        return std::unique_ptr<chat::post_message>(channel, text, SLACK_FWD(os)...);
    }
};
} //namespace endpoints
} //namespace slack