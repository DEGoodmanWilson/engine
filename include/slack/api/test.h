//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/api/parameter/test.h>
#include <slack/api/response/test.h>
#include <slack/api/impl/test.h>

namespace slack
{
namespace api
{

template<typename T>
void set_option(impl::test &impl, T &&t)
{
    impl.set_option(SLACK_FWD(t));
}

template<typename T, typename... Ts>
void set_option(impl::test &impl, T &&t, Ts &&... ts)
{
    set_option(impl, SLACK_FWD(t));
    set_option(impl, SLACK_FWD(ts)...);
}

template<typename ...Ts>
::slack::api::response::test test()
{
    class impl::test impl;
    return impl.get_response();
}

template<typename ...Ts>
::slack::api::response::test test(Ts &&...ts)
{
    class impl::test impl;
    set_option(impl, std::forward<Ts>(ts)...);
    return impl.get_response();
}

}
} //namespace slack