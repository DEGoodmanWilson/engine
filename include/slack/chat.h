//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/parameter/chat.h>
#include <slack/response/chat.h>
#include <string>


namespace slack
{

namespace chat
{

class delete_wrapper
{
public:
    delete_wrapper(const ts &ts, const channel_id &channel) : ts_{ts}, channel_{channel} {}

    ::slack::response::chat::delete_it get_response();
private:
    ts ts_;
    channel_id channel_;

};

::slack::response::chat::delete_it delete_it(ts ts, channel_id channel);

class post_message_wrapper
{

};

class update_wrapper
{

};

//class test_wrapper
//{
//public:
//    test_wrapper() = default;
//
//    ::slack::response::api::test get_response();
//
//    void set_option(const error &error)
//    { error_ = error; }
//
//    void set_option(error &&error)
//    { error_ = std::move(error); }
//
//    void set_option(const foo &foo)
//    { foo_ = foo; }
//
//    void set_option(foo &&foo)
//    { foo_ = std::move(foo); }
//
//private:
//    error error_;
//    foo foo_;
//};
//
//
//template<typename T>
//void set_option(test_wrapper &wrapper, T &&t)
//{
//    wrapper.set_option(SLACK_FWD(t));
//}
//
//template<typename T, typename... Ts>
//void set_option(test_wrapper &wrapper, T &&t, Ts &&... ts)
//{
//    set_option(wrapper, SLACK_FWD(t));
//    set_option(wrapper, SLACK_FWD(ts)...);
//}
//
//template<typename ...Ts>
//::slack::response::api::test test()
//{
//    class test_wrapper wrapper;
//    return wrapper.get_response();
//}
//
//template<typename ...Ts>
//::slack::response::api::test test(Ts &&...ts)
//{
//    class test_wrapper wrapper;
//    set_option(wrapper, std::forward<Ts>(ts)...);
//    return wrapper.get_response();
//}


} //namespace api
} //namespace slack