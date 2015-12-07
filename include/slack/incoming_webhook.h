//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/attachment.h>

namespace slack { namespace incoming_webhook
{

namespace parameter { namespace payload
{

MAKE_STRING_LIKE(text);

using channel_id = slack::channel_id;

MAKE_STRING_LIKE(username);

MAKE_BOOL_LIKE(mrkdwn);

MAKE_STRING_LIKE(icon_emoji);

using attachments = std::vector<slack::incoming_webhook::attachment>;

enum class response_type
{
    in_channel,
    ephemeral,
};

}} //namespace payload parameter

class payload
{
public:
    template<typename ...Os>
    payload(const parameter::payload::text &text)
            : text_{text}
    { }

    template<typename ...Os>
    payload(const parameter::payload::text &text, Os &&...os)
            : text_{text}
    {
        slack::set_option<payload>(*this, std::forward<Os>(os)...);
    }

    template<typename ...Os>
    payload(const parameter::payload::attachments &attachments)
            : attachments_{attachments}
    { }

    template<typename ...Os>
    payload(const parameter::payload::attachments &attachments, Os &&...os)
            : attachments_{attachments}
    {
        slack::set_option<payload>(*this, std::forward<Os>(os)...);
    }

    operator std::string();

    void set_option(const parameter::payload::text &text)
    { text_ = text; }

    void set_option(parameter::payload::text &&text)
    { text_ = std::move(text); }

    void set_option(const parameter::payload::channel_id &channel)
    { channel_ = channel; }

    void set_option(parameter::payload::channel_id &&channel)
    { channel_ = std::move(channel); }

    void set_option(const parameter::payload::username &username)
    { username_ = username; }

    void set_option(parameter::payload::username &&username)
    { username_ = std::move(username); }

    void set_option(const parameter::payload::icon_emoji &icon_emoji)
    { icon_emoji_ = icon_emoji; }

    void set_option(parameter::payload::icon_emoji &&icon_emoji)
    { icon_emoji_ = std::move(icon_emoji); }

    void set_option(const parameter::payload::mrkdwn &mrkdwn)
    { mrkdwn_ = mrkdwn; }

    void set_option(parameter::payload::mrkdwn &&mrkdwn)
    { mrkdwn_ = std::move(mrkdwn); }

    void set_option(const parameter::payload::attachments &attachments)
    { attachments_ = attachments; }

    void set_option(parameter::payload::attachments &&attachments)
    { attachments_ = std::move(attachments); }

    void set_option(const parameter::payload::response_type &response_type)
    { response_type_ = response_type; }

    void set_option(parameter::payload::response_type &&response_type)
    { response_type_ = std::move(response_type); }

private:

    std::experimental::optional<parameter::payload::text> text_;
    std::experimental::optional<parameter::payload::channel_id> channel_;
    std::experimental::optional<parameter::payload::username> username_;
    std::experimental::optional<parameter::payload::icon_emoji> icon_emoji_;
    std::experimental::optional<parameter::payload::mrkdwn> mrkdwn_;
    std::experimental::optional<parameter::payload::attachments> attachments_;
    std::experimental::optional<parameter::payload::response_type> response_type_;
};

}} //namespace incoming_webhook slack