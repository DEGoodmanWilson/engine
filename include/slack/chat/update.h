//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/chat/parameter/update.h>
#include <slack/chat/response/update.h>
#include <slack/chat/impl/update.h>

namespace slack
{
namespace chat
{

template<typename T>
void set_option(impl::update &impl, T &&t)
{
    impl.set_option(SLACK_FWD(t));
}

template<typename T, typename... Ts>
void set_option(impl::update &impl, T &&t, Ts &&... ts)
{
    set_option(impl, SLACK_FWD(t));
    set_option(impl, SLACK_FWD(ts)...);
}

template<typename ...Ts>
response::update update(const parameter::update::ts &ts,
                        const parameter::update::channel_id &channel,
                        const parameter::update::text &text)
{
    class impl::update impl{ts, channel, text};
    return impl.get_response();
}

template<typename ...Ts>
response::update update(const parameter::update::ts &ts,
                        const parameter::update::channel_id &channel,
                        const parameter::update::text &text,
                        Ts &&...tss)
{
    class impl::update impl{ts, channel, text};
    set_option(impl, std::forward<Ts>(tss)...);
    return impl.get_response();
}

} //namespace chat
} //namespace slack