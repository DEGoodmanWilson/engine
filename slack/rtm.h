//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <string>
#include <slack/set_option.h>
#include <slack/web/rtm.start.h>
#include <slack/base/slack_delegate.h>

namespace slack
{

namespace containers
{
class rtm
{
public:
    rtm(slack_delegate *delegate) : delegate_{delegate}
    { }

    template<typename ...Os>
    ::slack::rtm::start start() const
    {
        return ::slack::rtm::start{delegate_->token()};
    }

    template<typename ...Os>
    ::slack::rtm::start start(Os &&...os) const
    {
        return ::slack::rtm::start{delegate_->token(), SLACK_FWD(os)...};
    }

private:
    const slack_delegate *delegate_;
};
} //namespace endpoints
} //namespace slack