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
    std::unique_ptr<::slack::chat::postMessage> postMessage(const channel_id &channel, const std::string &text)
    {
        return std::make_unique<::slack::chat::postMessage>(channel, text);
    }

    template<typename ...Os>
    std::unique_ptr<::slack::chat::postMessage> postMessage(const channel_id &channel, const std::string &text, Os &&...os)
    {
        return std::make_unique<::slack::chat::postMessage>(channel, text, SLACK_FWD(os)...);
    }
};
} //namespace endpoints
} //namespace slack