//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <string>
#include <slack/set_option.h>
#include <slack/web/channels.create.h>
#include <slack/web/channels.archive.h>
#include <slack/web/channels.rename.h>
#include <slack/web/channels.list.h>
#include <slack/base/slack_delegate.h>

namespace slack
{

namespace containers
{
class channels
{
public:
    channels(slack_delegate *delegate) : delegate_{delegate}
    {}

    template<class CHANNEL, typename ...Os>
    ::slack::channels::archive archive(CHANNEL &&channel) const
    {
        return ::slack::channels::archive{delegate_->token(), std::forward<CHANNEL>(channel)};
    }

    template<class CHANNEL, typename ...Os>
    ::slack::channels::archive archive(CHANNEL &&channel, Os &&...os) const
    {
        return ::slack::channels::archive{delegate_->token(), std::forward<CHANNEL>(channel), SLACK_FWD(os)...};
    }


    template<class NAME>
    ::slack::channels::create create(NAME &&name) const
    {
        return ::slack::channels::create{delegate_->token(), std::forward<NAME>(name)};
    };


    template<typename ...Os>
    ::slack::channels::list list() const
    {
        return ::slack::channels::list{delegate_->token()};
    }

    template<typename ...Os>
    ::slack::channels::list list(Os &&...os) const
    {
        return ::slack::channels::list{delegate_->token(), SLACK_FWD(os)...};
    }


    template<class CHANNEL, class NAME>
    ::slack::channels::rename rename(CHANNEL &&channel, NAME &&name) const
    {
        return ::slack::channels::rename{delegate_->token(), std::forward<CHANNEL>(channel), std::forward<NAME>(name)};
    };


private:
    const slack_delegate *delegate_;
};
} //namespace endpoints
} //namespace slack