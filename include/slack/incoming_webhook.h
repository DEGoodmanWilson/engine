//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/attachment.h>

namespace slack { namespace incoming_webhook
{

namespace parameter
{

MAKE_STRING_LIKE(text);

using channel_id = slack::channel_id;

MAKE_STRING_LIKE(username);

MAKE_BOOL_LIKE(mrkdwn);

MAKE_STRING_LIKE(icon_emoji);

using attachment = slack::attachment::attachment;

using attachments = std::vector<attachment>;enum class response_type
{
    in_channel,
    ephemeral,
};

} //namespace parameter

class payload
{
public:
    payload(const parameter::text &text);
    payload(const parameter::attachments &attachments);

    operator std::string();

    void set_option(const parameter::text &text)
    { text_ = text; }

    void set_option(parameter::text &&text)
    { text_ = std::move(text); }

    void set_option(const parameter::channel_id &channel)
    { channel_ = channel; }

    void set_option(parameter::channel_id &&channel)
    { channel_ = std::move(channel); }

    void set_option(const parameter::username &username)
    { username_ = username; }

    void set_option(parameter::username &&username)
    { username_ = std::move(username); }

    void set_option(const parameter::icon_emoji &icon_emoji)
    { icon_emoji_ = icon_emoji; }

    void set_option(parameter::icon_emoji &&icon_emoji)
    { icon_emoji_ = std::move(icon_emoji); }

    void set_option(const parameter::mrkdwn &mrkdwn)
    { mrkdwn_ = mrkdwn; }

    void set_option(parameter::mrkdwn &&mrkdwn)
    { mrkdwn_ = std::move(mrkdwn); }

    void set_option(const parameter::attachments &attachments)
    { attachments_ = attachments; }

    void set_option(parameter::attachments &&attachments)
    { attachments_ = std::move(attachments); }

    void set_option(const parameter::response_type &response_type)
    { response_type_ = response_type; }

    void set_option(parameter::response_type &&response_type)
    { response_type_ = std::move(response_type); }

private:

    std::experimental::optional<parameter::text> text_;
    std::experimental::optional<parameter::channel_id> channel_;
    std::experimental::optional<parameter::username> username_;
    std::experimental::optional<parameter::icon_emoji> icon_emoji_;
    std::experimental::optional<parameter::mrkdwn> mrkdwn_;
    std::experimental::optional<parameter::attachments> attachments_;
    std::experimental::optional<parameter::response_type> response_type_;
};

template<typename ...Os>
payload create_payload(const parameter::text &text)
{
    return {text};
}

template<typename ...Os>
payload create_payload(const parameter::text &text, Os &&...os)
{
    payload p{text};
    slack::set_option<decltype(p)>(p, std::forward<Os>(os)...);
    return p;
}

template<typename ...Os>
payload create_payload(const parameter::attachments &attachments)
{
    return {attachments};
}

template<typename ...Os>
payload create_payload(const parameter::attachments &attachments, Os &&...os)
{
    payload p{attachments};
    slack::set_option<decltype(p)>(p, std::forward<Os>(os)...);
    return p;
}

}} //namespace incoming_webhook slack