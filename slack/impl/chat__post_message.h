//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <string>
#include <slack/types.h>
#include <slack/attachment.h>
#include <slack/optional.hpp>

namespace slack
{

namespace chat
{
namespace postMessage
{

MAKE_STRING_LIKE(username);
MAKE_BOOL_LIKE(as_user);
enum class parse
{
    none = 0,
    full,
};
MAKE_BOOL_LIKE(link_names);
using attachments = std::vector<slack::attachment>;
MAKE_BOOL_LIKE(unfurl_links);
MAKE_BOOL_LIKE(unfurl_media);
MAKE_STRING_LIKE(icon_url);
MAKE_STRING_LIKE(icon_emoji);

} //namespace postMessage
} //namespace chat

class chat__post_message_
{
public:
    message execute();

    // parameter setters //TODO can these be protected?
    void set_option(const chat::postMessage::username &username)
    { username_ = username; }

    void set_option(chat::postMessage::username &&username)
    { username_ = std::move(username); }

    void set_option(const chat::postMessage::as_user &as_user)
    { as_user_ = as_user; }

    void set_option(chat::postMessage::as_user &&as_user)
    { as_user_ = std::move(as_user); }

    void set_option(const chat::postMessage::parse &parse)
    { parse_ = parse; }

    void set_option(chat::postMessage::parse &&parse)
    { parse_ = std::move(parse); }

    void set_option(const chat::postMessage::link_names &link_names)
    { link_names_ = link_names; }

    void set_option(chat::postMessage::link_names &&link_names)
    { link_names_ = std::move(link_names); }

    void set_option(const chat::postMessage::attachments &attachments)
    { attachments_ = attachments; }

    void set_option(chat::postMessage::attachments &&attachments)
    { attachments_ = std::move(attachments); }

    void set_option(const chat::postMessage::unfurl_links &unfurl_links)
    { unfurl_links_ = unfurl_links; }

    void set_option(chat::postMessage::unfurl_links &&unfurl_links)
    { unfurl_links_ = std::move(unfurl_links); }

    void set_option(const chat::postMessage::unfurl_media &unfurl_media)
    { unfurl_media_ = unfurl_media; }

    void set_option(chat::postMessage::unfurl_media &&unfurl_media)
    { unfurl_media_ = std::move(unfurl_media); }

    void set_option(const chat::postMessage::icon_url &icon_url)
    { icon_url_ = icon_url; }

    void set_option(chat::postMessage::icon_url &&icon_url)
    { icon_url_ = std::move(icon_url); }

    void set_option(const chat::postMessage::icon_emoji &icon_emoji)
    { icon_emoji_ = icon_emoji; }

    void set_option(chat::postMessage::icon_emoji &&icon_emoji)
    { icon_emoji_ = std::move(icon_emoji); }

private:
    channel_id channel_;
    std::string text_;
    std::experimental::optional<chat::postMessage::username> username_;
    std::experimental::optional<chat::postMessage::as_user> as_user_;
    std::experimental::optional<chat::postMessage::parse> parse_;
    std::experimental::optional<chat::postMessage::link_names> link_names_;
    std::experimental::optional<chat::postMessage::attachments> attachments_;
    std::experimental::optional<chat::postMessage::unfurl_links> unfurl_links_;
    std::experimental::optional<chat::postMessage::unfurl_media> unfurl_media_;
    std::experimental::optional<chat::postMessage::icon_url> icon_url_;
    std::experimental::optional<chat::postMessage::icon_emoji> icon_emoji_;
};
} //namespace slack