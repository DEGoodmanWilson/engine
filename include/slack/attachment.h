//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>

namespace slack
{
namespace attachment
{

namespace parameter
{

MAKE_BOOL_LIKE(is_short);  //because "short" is a keyword

} //namepsace parameter


struct field
{
public:
    field(const std::string &title, const std::string &value);

    template<class Json>
    operator Json();

    void set_option(const parameter::is_short &is_short)
    { is_short_ = is_short; }

    void set_option(parameter::is_short &&is_short)
    { is_short_ = std::move(is_short); }

private:
    std::string title_;
    std::string value_;
    std::experimental::optional<parameter::is_short> is_short_;
};

template<typename ...Os>
field create_field(const std::string& title, const std::string& value)
{
    return field{title, value};
}

template<typename ...Os>
field create_field(const std::string& title, const std::string& value, Os &&...os)
{
    field f{title, value};
    slack::set_option<decltype(f)>(f, std::forward<Os>(os)...);
    return f;
}

namespace parameter
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

using fields = std::vector<field>;
enum class mrkdwn_in_fields
{
    text,
    pretext,
    fallback,
};
using mrkdwn_in = std::vector<mrkdwn_in_fields>;

MAKE_STRING_LIKE(image_url);

MAKE_STRING_LIKE(thumb_url);

} //namespace parameter

class attachment
{
public:
    attachment() = default;

    template<class Json>
    operator Json();

    void set_option(const parameter::fallback &fallback)
    { fallback_ = fallback; }

    void set_option(parameter::fallback &&fallback)
    { fallback_ = std::move(fallback); }

    void set_option(const parameter::color &color)
    { color_ = color; }

    void set_option(parameter::color &&color)
    { color_ = std::move(color); }

    void set_option(const parameter::pretext &pretext)
    { pretext_ = pretext; }

    void set_option(parameter::pretext &&pretext)
    { pretext_ = std::move(pretext); }

    void set_option(const parameter::author_name &author_name)
    { author_name_ = author_name; }

    void set_option(parameter::author_name &&author_name)
    { author_name_ = std::move(author_name); }

    void set_option(const parameter::author_link &author_link)
    { author_link_ = author_link; }

    void set_option(parameter::author_link &&author_link)
    { author_link_ = std::move(author_link); }

    void set_option(const parameter::author_icon &author_icon)
    { author_icon_ = author_icon; }

    void set_option(parameter::author_icon &&author_icon)
    { author_icon_ = std::move(author_icon); }

    void set_option(const parameter::title &title)
    { title_ = title; }

    void set_option(parameter::title &&title)
    { title_ = std::move(title); }

    void set_option(const parameter::title_link &title_link)
    { title_link_ = title_link; }

    void set_option(parameter::title_link &&title_link)
    { title_link_ = std::move(title_link); }

    void set_option(const parameter::text &text)
    { text_ = text; }

    void set_option(parameter::text &&text)
    { text_ = std::move(text); }

    void set_option(const parameter::fields &fields)
    { fields_ = fields; }

    void set_option(parameter::fields &&fields)
    { fields_ = std::move(fields); }

    void set_option(const parameter::mrkdwn_in &mrkdwn_in)
    { mrkdwn_in_ = mrkdwn_in; }

    void set_option(parameter::mrkdwn_in &&mrkdwn_in)
    { mrkdwn_in_ = std::move(mrkdwn_in); }

    void set_option(const parameter::image_url &image_url)
    { image_url_ = image_url; }

    void set_option(parameter::image_url &&image_url)
    { image_url_ = std::move(image_url); }

    void set_option(const parameter::thumb_url &thumb_url)
    { thumb_url_ = thumb_url; }

    void set_option(parameter::thumb_url &&thumb_url)
    { thumb_url_ = std::move(thumb_url); }

private:

    std::experimental::optional<parameter::fallback> fallback_;
    std::experimental::optional<parameter::color> color_;
    std::experimental::optional<parameter::pretext> pretext_;
    std::experimental::optional<parameter::author_name> author_name_;
    std::experimental::optional<parameter::author_link> author_link_;
    std::experimental::optional<parameter::author_icon> author_icon_;
    std::experimental::optional<parameter::title> title_;
    std::experimental::optional<parameter::title_link> title_link_;
    std::experimental::optional<parameter::text> text_;
    std::experimental::optional<parameter::fields> fields_;
    std::experimental::optional<parameter::mrkdwn_in> mrkdwn_in_;
    std::experimental::optional<parameter::image_url> image_url_;
    std::experimental::optional<parameter::thumb_url> thumb_url_;
};

template<typename ...Os>
attachment create_attachment()
{
    return attachment{};
}

template<typename ...Os>
attachment create_attachment(Os &&...os)
{
    attachment a;
    slack::set_option<decltype(a)>(a, std::forward<Os>(os)...);
    return a;
}

} //namespace attachment
} //namespace slack