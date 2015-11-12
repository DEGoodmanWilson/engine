//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/parameter/channels.h>
#include <slack/response/channels.h>
#include <string>


namespace slack
{

namespace channels
{


class list_wrapper
{
public:
    list_wrapper() : exclude_archived_{false} {};

    ::slack::response::channels::list get_response();

    void set_option(exclude_archived exclude_archived)
    { exclude_archived_ = exclude_archived; }

private:
    exclude_archived exclude_archived_;
};


template<typename T>
void set_option(list_wrapper &wrapper, T &&t)
{
    wrapper.set_option(SLACK_FWD(t));
}

template<typename T, typename... Ts>
void set_option(list_wrapper &wrapper, T &&t, Ts &&... ts)
{
    set_option(wrapper, SLACK_FWD(t));
    set_option(wrapper, SLACK_FWD(ts)...);
}

template<typename ...Ts>
::slack::response::channels::list list()
{
    class list_wrapper wrapper;
    return wrapper.get_response();
}

template<typename ...Ts>
::slack::response::channels::list list(Ts &&...ts)
{
    class list_wrapper wrapper;
    set_option(wrapper, std::forward<Ts>(ts)...);
    return wrapper.get_response();
}


} //namespace api
} //namespace slack