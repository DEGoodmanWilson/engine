//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <string>
#include <slack/set_option.h>
#include <slack/web/chat.postMessage.h>
#include <slack/web/chat.update.h>
#include <slack/web/chat.delete.h>
#include <slack/base/slack_delegate.h>

namespace slack
{

namespace containers
{
class chat
{
public:
    chat(slack_delegate *delegate) : delegate_{delegate}
    {}

    template<class CHANNEL, class TEXT, typename ...Os>
    ::slack::chat::postMessage postMessage(CHANNEL &&channel, TEXT &&text) const
    {
        return ::slack::chat::postMessage{delegate_->token(), std::forward<CHANNEL>(channel), std::forward<TEXT>(text)};
    }

    template<class CHANNEL, class TEXT, typename ...Os>
    ::slack::chat::postMessage postMessage(CHANNEL &&channel, TEXT &&text, Os &&...os) const
    {
        return ::slack::chat::postMessage{delegate_->token(), std::forward<CHANNEL>(channel), std::forward<TEXT>(text),
                                          SLACK_FWD(os)...};
    }


    template<class TS, class CHANNEL, class TEXT, typename ...Os>
    ::slack::chat::update update(TS &&ts, CHANNEL &&channel, TEXT &&text) const
    {
        return ::slack::chat::update{delegate_->token(), std::forward<TS>(ts), std::forward<CHANNEL>(channel),
                                     std::forward<TEXT>(text)};
    }

    template<class TS, class CHANNEL, class TEXT, typename ...Os>
    ::slack::chat::update update(TS &&ts, CHANNEL &&channel, TEXT &&text, Os &&...os) const
    {
        return ::slack::chat::update{delegate_->token(), std::forward<TS>(ts), std::forward<CHANNEL>(channel),
                                     std::forward<TEXT>(text), SLACK_FWD(os)...};
    }


    template<class TS, class CHANNEL>
    ::slack::chat::delete_it delete_it(TS &&ts, CHANNEL &&channel) const
    {
        return ::slack::chat::delete_it{delegate_->token(), std::forward<TS>(ts), std::forward<CHANNEL>(channel)};
    }

private:
    const slack_delegate *delegate_;
};
} //namespace endpoints
} //namespace slack