//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>

namespace slack { namespace incoming_webhook
{

namespace parameter { namespace field
{

MAKE_BOOL_LIKE(is_short);  //because "short" is a keyword

} }//namepsace field parameter


class field
{
public:
//    field(const std::string &title, const std::string &value);

    template<typename ...Os>
    field(const std::string& title, const std::string& value)
            : title_{title}, value_{value}

    { }

    template<typename ...Os>
    field(const std::string& title, const std::string& value, Os &&...os)
    : title_{title}, value_{value}
    {
        slack::set_option<field>(*this, std::forward<Os>(os)...);
    }

    template<class Json>
    operator Json();

    void set_option(const parameter::field::is_short &is_short)
    { is_short_ = is_short; }

    void set_option(parameter::field::is_short &&is_short)
    { is_short_ = std::move(is_short); }

private:
    std::string title_;
    std::string value_;
    std::experimental::optional<parameter::field::is_short> is_short_;
};

namespace parameter { namespace attachment
{

MAKE_STRING_LIKE(fallback);

MAKE_STRING_LIKE(color);

MAKE_STRING_LIKE(pretext);

MAKE_STRING_LIKE(author_name);

MAKE_STRING_LIKE(author_link);

MAKE_STRING_LIKE(author_icon);

MAKE_STRING_LIKE(title);

MAKE_STRING_LIKE(title_link);

MAKE_STRING_LIKE(text);

using fields = std::vector<incoming_webhook::field>;
enum class mrkdwn_in_fields
{
    text,
    pretext,
    fallback,
};
using mrkdwn_in = std::vector<mrkdwn_in_fields>;

MAKE_STRING_LIKE(image_url);

MAKE_STRING_LIKE(thumb_url);

} } //namespace attachment parameter

class attachment
{
public:
    template<typename ...Os>
    attachment()
    { }

    template<typename ...Os>
    attachment(int i, Os &&...os)
    {
        slack::set_option<attachment>(*this, std::forward<Os>(os)...);
    }

    template<class Json>
    operator Json();

    void set_option(const parameter::attachment::fallback &fallback)
    { fallback_ = fallback; }

    void set_option(parameter::attachment::fallback &&fallback)
    { fallback_ = std::move(fallback); }

    void set_option(const parameter::attachment::color &color)
    { color_ = color; }

    void set_option(parameter::attachment::color &&color)
    { color_ = std::move(color); }

    void set_option(const parameter::attachment::pretext &pretext)
    { pretext_ = pretext; }

    void set_option(parameter::attachment::pretext &&pretext)
    { pretext_ = std::move(pretext); }

    void set_option(const parameter::attachment::author_name &author_name)
    { author_name_ = author_name; }

    void set_option(parameter::attachment::author_name &&author_name)
    { author_name_ = std::move(author_name); }

    void set_option(const parameter::attachment::author_link &author_link)
    { author_link_ = author_link; }

    void set_option(parameter::attachment::author_link &&author_link)
    { author_link_ = std::move(author_link); }

    void set_option(const parameter::attachment::author_icon &author_icon)
    { author_icon_ = author_icon; }

    void set_option(parameter::attachment::author_icon &&author_icon)
    { author_icon_ = std::move(author_icon); }

    void set_option(const parameter::attachment::title &title)
    { title_ = title; }

    void set_option(parameter::attachment::title &&title)
    { title_ = std::move(title); }

    void set_option(const parameter::attachment::title_link &title_link)
    { title_link_ = title_link; }

    void set_option(parameter::attachment::title_link &&title_link)
    { title_link_ = std::move(title_link); }

    void set_option(const parameter::attachment::text &text)
    { text_ = text; }

    void set_option(parameter::attachment::text &&text)
    { text_ = std::move(text); }

    void set_option(const parameter::attachment::fields &fields)
    { fields_ = fields; }

    void set_option(parameter::attachment::fields &&fields)
    { fields_ = std::move(fields); }

    void set_option(const parameter::attachment::mrkdwn_in &mrkdwn_in)
    { mrkdwn_in_ = mrkdwn_in; }

    void set_option(parameter::attachment::mrkdwn_in &&mrkdwn_in)
    { mrkdwn_in_ = std::move(mrkdwn_in); }

    void set_option(const parameter::attachment::image_url &image_url)
    { image_url_ = image_url; }

    void set_option(parameter::attachment::image_url &&image_url)
    { image_url_ = std::move(image_url); }

    void set_option(const parameter::attachment::thumb_url &thumb_url)
    { thumb_url_ = thumb_url; }

    void set_option(parameter::attachment::thumb_url &&thumb_url)
    { thumb_url_ = std::move(thumb_url); }

private:

    std::experimental::optional<parameter::attachment::fallback> fallback_;
    std::experimental::optional<parameter::attachment::color> color_;
    std::experimental::optional<parameter::attachment::pretext> pretext_;
    std::experimental::optional<parameter::attachment::author_name> author_name_;
    std::experimental::optional<parameter::attachment::author_link> author_link_;
    std::experimental::optional<parameter::attachment::author_icon> author_icon_;
    std::experimental::optional<parameter::attachment::title> title_;
    std::experimental::optional<parameter::attachment::title_link> title_link_;
    std::experimental::optional<parameter::attachment::text> text_;
    std::experimental::optional<parameter::attachment::fields> fields_;
    std::experimental::optional<parameter::attachment::mrkdwn_in> mrkdwn_in_;
    std::experimental::optional<parameter::attachment::image_url> image_url_;
    std::experimental::optional<parameter::attachment::thumb_url> thumb_url_;
};

} //namespace incoming_webhook
} //namespace slack