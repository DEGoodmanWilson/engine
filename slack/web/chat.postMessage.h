//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/attachment.h>
#include <slack/set_option.h>
#include <base/response.h>
#include <slack/event/message.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>

namespace slack { namespace chat
{

class postMessage : public slack::base::response
{
public:
    template<typename ...Os>
    postMessage(const std::string& token, const channel_id& channel, const std::string& text)
            : response{token}, channel_{channel}, text_{text}
    {
        initialize_();
    }

    template<typename ...Os>
    postMessage(const std::string& token, const channel_id& channel, const std::string& text, Os &&...os)
            : response{token}, channel_{channel}, text_{text}
    {
        slack::set_option<postMessage>(*this, std::forward<Os>(os)...);
        initialize_();
    }

    // parameters
    struct parameter
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
    };

    // errors
    struct error : public slack::base::error
    {
        static const std::string MESSAGE_NOT_FOUND;
        static const std::string CHANNEL_NOT_FOUND;
        static const std::string CANT_DELETE_MESSAGE;
        static const std::string COMPLIANCE_EXPORTS_PREVENT_DELETION;
        static const std::string NOT_AUTHED;
        static const std::string INVALID_AUTH;
        static const std::string ACCOUNT_INACTIVE;
    };

    // response
    std::experimental::optional<slack::channel_id> channel;
    std::experimental::optional<slack::ts> ts;
    std::experimental::optional<slack::event::message> message;

    // parameter setters //TODO can these be protected?
    void set_option(const parameter::username &username)
    { username_ = username; }

    void set_option(parameter::username &&username)
    { username_ = std::move(username); }

    void set_option(const parameter::as_user &as_user)
    { as_user_ = as_user; }

    void set_option(parameter::as_user &&as_user)
    { as_user_ = std::move(as_user); }

    void set_option(const parameter::parse &parse)
    { parse_ = parse; }

    void set_option(parameter::parse &&parse)
    { parse_ = std::move(parse); }

    void set_option(const parameter::link_names &link_names)
    { link_names_ = link_names; }

    void set_option(parameter::link_names &&link_names)
    { link_names_ = std::move(link_names); }

    void set_option(const parameter::attachments &attachments)
    { attachments_ = attachments; }

    void set_option(parameter::attachments &&attachments)
    { attachments_ = std::move(attachments); }

    void set_option(const parameter::unfurl_links &unfurl_links)
    { unfurl_links_ = unfurl_links; }

    void set_option(parameter::unfurl_links &&unfurl_links)
    { unfurl_links_ = std::move(unfurl_links); }

    void set_option(const parameter::unfurl_media &unfurl_media)
    { unfurl_media_ = unfurl_media; }

    void set_option(parameter::unfurl_media &&unfurl_media)
    { unfurl_media_ = std::move(unfurl_media); }

    void set_option(const parameter::icon_url &icon_url)
    { icon_url_ = icon_url; }

    void set_option(parameter::icon_url &&icon_url)
    { icon_url_ = std::move(icon_url); }

    void set_option(const parameter::icon_emoji &icon_emoji)
    { icon_emoji_ = icon_emoji; }

    void set_option(parameter::icon_emoji &&icon_emoji)
    { icon_emoji_ = std::move(icon_emoji); }

private:
    void initialize_();

    channel_id channel_;
    std::string text_;
    std::experimental::optional<parameter::username> username_;
    std::experimental::optional<parameter::as_user> as_user_;
    std::experimental::optional<parameter::parse> parse_;
    std::experimental::optional<parameter::link_names> link_names_;
    std::experimental::optional<parameter::attachments> attachments_;
    std::experimental::optional<parameter::unfurl_links> unfurl_links_;
    std::experimental::optional<parameter::unfurl_media> unfurl_media_;
    std::experimental::optional<parameter::icon_url> icon_url_;
    std::experimental::optional<parameter::icon_emoji> icon_emoji_;
};

} } //namespace chat slack