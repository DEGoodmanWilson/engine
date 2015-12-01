//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <slack/base/impl.h>
#include <string>
#include <vector>
#include <optional/optional.hpp>

namespace slack
{
namespace chat
{

/*************************************************************/
// MARK: - Parameters

namespace parameter
{
namespace post_message
{

MAKE_STRING_LIKE(username);
MAKE_BOOL_LIKE(as_user);
enum class parse
{
    none = 0,
    full,
};
MAKE_BOOL_LIKE(link_names);
//TODO This one needs to be better!!
MAKE_STRING_LIKE(attachments);
MAKE_BOOL_LIKE(unfurl_links);
MAKE_BOOL_LIKE(unfurl_media);
MAKE_STRING_LIKE(icon_url);
MAKE_STRING_LIKE(icon_emoji);

} //namespace post_message
} //namespace parameter

/*************************************************************/
// MARK: - Response Errors

namespace response
{
namespace error
{
namespace post_message
{

const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
const auto MESSAGE_NOT_FOUND = std::string{"message_not_found"};
const auto CHANNEL_NOT_FOUND = std::string{"channel_not_found"};
const auto CANT_DELETE_MESSAGE = std::string{"cant_delete_message"};
const auto COMPLIANCE_EXPORTS_PREVENT_DELETION = std::string{"compliance_exports_prevent_deletion"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};

} //namespace post_message
} //namespace error
} //namespace response


/*************************************************************/
// MARK: - Response

namespace response
{

struct post_message :
        public slack::base::response
{
    post_message(const std::string &raw_json);

    std::experimental::optional<channel_id> channel;
    std::experimental::optional<ts> ts;
    std::experimental::optional<message> message;
};

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

class post_message :
        public slack::base::impl<response::post_message>
{
public:
    post_message(const channel_id &channel, const std::string &text);
    //TODO can these be moved into the base class?
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
    channel_id channel_;
    std::string text_;
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


/*************************************************************/
// MARK: - Public Interface


template<typename ...Os>
response::post_message post_message(const channel_id& channel, const std::string& text)
{
    class impl::post_message impl{channel, text};
    return impl.get_response();
}

template<typename ...Os>
response::post_message post_message(const channel_id& channel, const std::string& text, Os &&...os)
{
    class impl::post_message impl{channel, text};
    set_option<decltype(impl)>(impl, std::forward<Os>(os)...);
    return impl.get_response();
}

} //namespace chat
} //namespace slack