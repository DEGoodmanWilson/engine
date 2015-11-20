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
    delete_wrapper(const ts &ts, const channel_id &channel) : ts_{ts}, channel_{channel}
    { }

    ::slack::response::chat::delete_it get_response();

private:
    ts ts_;
    channel_id channel_;

};

::slack::response::chat::delete_it delete_it(ts ts, channel_id channel);

class post_message_wrapper
{
public:

    post_message_wrapper(const channel_id &channel, const text &text) :
            channel_(channel), text_(text)
    { }

    void set_option(const as_user &as_user)
    { as_user_ = as_user; }

    void set_option(as_user &&as_user)
    { as_user_ = std::move(as_user); }

    void set_option(const parse &parse)
    { parse_ = parse; }

    void set_option(parse &&parse)
    { parse_ = std::move(parse); }

    void set_option(const link_names &link_names)
    { link_names_ = link_names; }

    void set_option(link_names &&link_names)
    { link_names_ = std::move(link_names); }

    void set_option(const attachments &attachments)
    { attachments_ = attachments; }

    void set_option(attachments &&attachments)
    { attachments_ = std::move(attachments); }

    void set_option(const unfurl_links &unfurl_links)
    { unfurl_links_ = unfurl_links; }

    void set_option(unfurl_links &&unfurl_links)
    { unfurl_links_ = std::move(unfurl_links); }

    void set_option(const unfurl_media &unfurl_media)
    { unfurl_media_ = unfurl_media; }

    void set_option(unfurl_media &&unfurl_media)
    { unfurl_media_ = std::move(unfurl_media); }

    void set_option(const icon_url &icon_url)
    { icon_url_ = icon_url; }

    void set_option(icon_url &&icon_url)
    { icon_url_ = std::move(icon_url); }

    void set_option(const icon_emoji &icon_emoji)
    { icon_emoji_ = icon_emoji; }

    void set_option(icon_emoji &&icon_emoji)
    { icon_emoji_ = std::move(icon_emoji); }

    ::slack::response::chat::post_message get_response();

private:
    channel_id channel_;
    text text_;
    std::experimental::optional<ts> ts_;
    std::experimental::optional<username> username_;
    std::experimental::optional<as_user> as_user_;
    std::experimental::optional<parse> parse_;
    std::experimental::optional<link_names> link_names_;
    std::experimental::optional<attachments> attachments_;
    std::experimental::optional<unfurl_links> unfurl_links_;
    std::experimental::optional<unfurl_media> unfurl_media_;
    std::experimental::optional<icon_url> icon_url_;
    std::experimental::optional<icon_emoji> icon_emoji_;
};

template<typename T>
void set_option(post_message_wrapper &wrapper, T &&t)
{
    wrapper.set_option(SLACK_FWD(t));
}

template<typename T, typename... Ts>
void set_option(post_message_wrapper &wrapper, T &&t, Ts &&... ts)
{
    set_option(wrapper, SLACK_FWD(t));
    set_option(wrapper, SLACK_FWD(ts)...);
}

template<typename ...Ts>
::slack::response::chat::post_message post_message(channel_id channel, text text)
{
    class post_message_wrapper wrapper{channel, text};
    return wrapper.get_response();
}

template<typename ...Ts>
::slack::response::chat::post_message post_message(channel_id channel, text text, Ts &&...ts)
{
    class post_message_wrapper wrapper{channel, text};
    set_option(wrapper, std::forward<Ts>(ts)...);
    return wrapper.get_response();
}

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