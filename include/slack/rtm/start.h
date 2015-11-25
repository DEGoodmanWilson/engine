//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/rtm/parameter/start.h>
#include <slack/rtm/response/start.h>
#include <slack/rtm/impl/start.h>

namespace slack
{
namespace rtm
{

template<typename T>
void set_option(impl::start &impl, T &&t)
{
    impl.set_option(SLACK_FWD(t));
}

template<typename T, typename... Ts>
void set_option(impl::start &impl, T &&t, Ts &&... ts)
{
    set_option(impl, SLACK_FWD(t));
    set_option(impl, SLACK_FWD(ts)...);
}

template<typename ...Ts>
response::start start()
{
    class impl::start impl;
    return impl.get_response();
}

template<typename ...Ts>
response::start start(Ts &&...ts)
{
    class impl::start impl;
    set_option(impl, std::forward<Ts>(ts)...);
    return impl.get_response();
}

} //namespace rtm
} //namespace slack