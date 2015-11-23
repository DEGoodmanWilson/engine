//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/chat/parameter/post_message.h>
#include <slack/chat/response/post_message.h>
#include <slack/chat/impl/post_message.h>

namespace slack
{
namespace chat
{

template<typename T>
void set_option(impl::post_message &impl, T &&t)
{
    impl.set_option(SLACK_FWD(t));
}

template<typename T, typename... Ts>
void set_option(impl::post_message &impl, T &&t, Ts &&... ts)
{
    set_option(impl, SLACK_FWD(t));
    set_option(impl, SLACK_FWD(ts)...);
}

template<typename ...Ts>
response::post_message post_message(parameter::post_message::channel_id channel, parameter::post_message::text text)
{
    class impl::post_message impl{channel, text};
    return impl.get_response();
}

template<typename ...Ts>
response::post_message post_message(parameter::post_message::channel_id channel, parameter::post_message::text text, Ts &&...ts)
{
    class impl::post_message impl{channel, text};
    set_option(impl, std::forward<Ts>(ts)...);
    return impl.get_response();
}

} //namespace chat
} //namespace slack