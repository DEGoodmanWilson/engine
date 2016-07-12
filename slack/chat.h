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

    template<class CHANNEL, class TEXT, typename ...Os>
    std::unique_ptr<::slack::chat::postMessage> postMessage(CHANNEL &&channel, TEXT &&text) const
    {
        return std::make_unique<::slack::chat::postMessage>(delegate_->token(), std::forward<CHANNEL>(channel), std::forward<TEXT>(text));
    }

    template<class CHANNEL, class TEXT, typename ...Os>
    std::unique_ptr<::slack::chat::postMessage> postMessage(CHANNEL &&channel, TEXT &&text, Os &&...os) const
    {
        return std::make_unique<::slack::chat::postMessage>(delegate_->token(), std::forward<CHANNEL>(channel), std::forward<TEXT>(text), SLACK_FWD(os)...);
    }

private:
    const slack_delegate *delegate_;
};
} //namespace endpoints
} //namespace slack