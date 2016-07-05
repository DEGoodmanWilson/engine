//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <string>
#include <slack/set_option.h>
#include <slack/web/chat.postMessage.h>
#include <slack/base/slack_delegate.h>

namespace slack
{

namespace containers
{
class chat
{
public:
    chat(slack_delegate *delegate) : delegate_{delegate}
    { }

    template<typename ...Os>
    std::unique_ptr<::slack::chat::postMessage> postMessage(const channel_id &channel, const std::string &text) const
    {
        return std::make_unique<::slack::chat::postMessage>(delegate_->token(), channel, text);
    }

    template<typename ...Os>
    std::unique_ptr<::slack::chat::postMessage> postMessage(const channel_id &channel,
                                                            const std::string &text,
                                                            Os &&...os) const
    {
        return std::make_unique<::slack::chat::postMessage>(delegate_->token(), channel, text, SLACK_FWD(os)...);
    }

private:
    const slack_delegate *delegate_;
};
} //namespace endpoints
} //namespace slack