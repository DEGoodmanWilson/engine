//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/channels/parameter/list.h>
#include <slack/channels/response/list.h>
#include <slack/channels/impl/list.h>

namespace slack
{
namespace channels
{

template<typename T>
void set_option(impl::list &impl, T &&t)
{
    impl.set_option(SLACK_FWD(t));
}

template<typename T, typename... Ts>
void set_option(impl::list &impl, T &&t, Ts &&... ts)
{
    set_option(impl, SLACK_FWD(t));
    set_option(impl, SLACK_FWD(ts)...);
}

template<typename ...Ts>
response::list list()
{
    class impl::list impl;
    return impl.get_response();
}

template<typename ...Ts>
response::list list(Ts &&...ts)
{
    class impl::list impl;
    set_option(impl, std::forward<Ts>(ts)...);
    return impl.get_response();
}

} //namespace channels
} //namespace slack