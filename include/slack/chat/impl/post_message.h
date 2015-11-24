//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/chat/response/post_message.h>
#include <slack/chat/parameter/post_message.h>

namespace slack
{
namespace chat
{
namespace impl
{

class post_message
{
public:

    post_message(const parameter::post_message::channel_id &channel, const parameter::post_message::text &text) :
            channel_(channel), text_(text)
    { }

    response::post_message get_response();

    void set_option(const parameter::post_message::username &username)
    { username_ = username; }

    void set_option(parameter::post_message::username &&username)
    { username_ = std::move(username); }

    void set_option(const parameter::post_message::as_user &as_user)
    { as_user_ = as_user; }

    void set_option(parameter::post_message::as_user &&as_user)
    { as_user_ = std::move(as_user); }

    void set_option(const parameter::post_message::parse &parse)
    { parse_ = parse; }

    void set_option(parameter::post_message::parse &&parse)
    { parse_ = std::move(parse); }

    void set_option(const parameter::post_message::link_names &link_names)
    { link_names_ = link_names; }

    void set_option(parameter::post_message::link_names &&link_names)
    { link_names_ = std::move(link_names); }

    void set_option(const parameter::post_message::attachments &attachments)
    { attachments_ = attachments; }

    void set_option(parameter::post_message::attachments &&attachments)
    { attachments_ = std::move(attachments); }

    void set_option(const parameter::post_message::unfurl_links &unfurl_links)
    { unfurl_links_ = unfurl_links; }

    void set_option(parameter::post_message::unfurl_links &&unfurl_links)
    { unfurl_links_ = std::move(unfurl_links); }

    void set_option(const parameter::post_message::unfurl_media &unfurl_media)
    { unfurl_media_ = unfurl_media; }

    void set_option(parameter::post_message::unfurl_media &&unfurl_media)
    { unfurl_media_ = std::move(unfurl_media); }

    void set_option(const parameter::post_message::icon_url &icon_url)
    { icon_url_ = icon_url; }

    void set_option(parameter::post_message::icon_url &&icon_url)
    { icon_url_ = std::move(icon_url); }

    void set_option(const parameter::post_message::icon_emoji &icon_emoji)
    { icon_emoji_ = icon_emoji; }

    void set_option(parameter::post_message::icon_emoji &&icon_emoji)
    { icon_emoji_ = std::move(icon_emoji); }


private:
    parameter::post_message::channel_id channel_;
    parameter::post_message::text text_;
    std::experimental::optional<parameter::post_message::username> username_;
    std::experimental::optional<parameter::post_message::as_user> as_user_;
    std::experimental::optional<parameter::post_message::parse> parse_;
    std::experimental::optional<parameter::post_message::link_names> link_names_;
    std::experimental::optional<parameter::post_message::attachments> attachments_;
    std::experimental::optional<parameter::post_message::unfurl_links> unfurl_links_;
    std::experimental::optional<parameter::post_message::unfurl_media> unfurl_media_;
    std::experimental::optional<parameter::post_message::icon_url> icon_url_;
    std::experimental::optional<parameter::post_message::icon_emoji> icon_emoji_;
};

} //namespace impl
} //namespace chat
} //namespace slack