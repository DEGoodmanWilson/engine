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

    responses::delete_it get_response();

private:
    ts ts_;
    channel_id channel_;

};

responses::delete_it delete_it(ts ts, channel_id channel);

class post_message_wrapper
{
public:

    post_message_wrapper(const channel_id &channel, const text &text) :
            channel_(channel), text_(text)
    { }

    void set_option(const username &username)
    { username_ = username; }

    void set_option(username &&username)
    { username_ = std::move(username); }

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

    ::slack::chat::responses::post_message get_response();

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
::slack::chat::responses::post_message post_message(channel_id channel, text text)
{
    class post_message_wrapper wrapper{channel, text};
    return wrapper.get_response();
}

template<typename ...Ts>
::slack::chat::responses::post_message post_message(channel_id channel, text text, Ts &&...ts)
{
    class post_message_wrapper wrapper{channel, text};
    set_option(wrapper, std::forward<Ts>(ts)...);
    return wrapper.get_response();
}

class update_wrapper
{

};



} //namespace api
} //namespace slack