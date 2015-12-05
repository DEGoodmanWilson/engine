//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/fwd.h>
#include <slack/set_option.h>
#include <string>
#include <vector>
#include <map>
#include <slack/optional.hpp>


#define MAKE_STRING_LIKE(x) class x : public std::string \
{ \
public: \
    x() = default; \
    x(const x &rhs) = default; \
    x(x &&rhs) = default; \
    x &operator=(const x &rhs) = default; \
    x &operator=(x &&rhs) = default; \
    x(const char *raw_string) : std::string(raw_string) {} \
    x(const char *raw_string, size_t length) : std::string(raw_string, length) {} \
    explicit x(size_t to_fill, char character) : std::string(to_fill, character) {} \
    x(const std::string &std_string) : std::string(std_string) {} \
    x(const std::string &std_string, size_t position, size_t length = std::string::npos) \
        : std::string(std_string, position, length) {} \
    explicit x(std::initializer_list<char> il) : std::string(il) {} \
    template<class InputIterator> \
    explicit x(InputIterator first, InputIterator last) \
        : std::string(first, last) {} \
}

#define MAKE_BOOL_LIKE(x) class x \
{ \
public: \
    x() = default; \
    x(const x &rhs) = default; \
    x(x &&rhs) = default; \
    x &operator=(const x &rhs) = default; \
    x &operator=(x &&rhs) = default; \
    x(bool new_val) : value{new_val} {} \
    x & operator=(bool && new_value) {value = new_value;} \
    explicit operator bool() {return value;} \
private: \
    bool value; \
}

namespace slack
{

//TODO NONE of these things should be just strings.

MAKE_STRING_LIKE(team_id);

MAKE_STRING_LIKE(user_id);

MAKE_STRING_LIKE(ts);

MAKE_STRING_LIKE(channel_id);

MAKE_STRING_LIKE(token);

MAKE_STRING_LIKE(scope);

struct message
{
    message() = default;

    template<class json>
    message(const json &parsed_json);

    std::string text;
    std::string username;
    std::string type; //TODO!
    std::experimental::optional<std::string> subtype; //TODO
    ts ts;
};

struct channel
{
    channel() = default;

    template<class json>
    channel(const json &parsed_json);

    struct topic
    {
        std::string value;
        user_id creator;
        int64_t last_set;
    };

    struct purpose
    {
        std::string value;
        user_id creator;
        int64_t last_set;
    };

    channel_id id;
    std::string name;
    bool is_channel;
    int64_t created;
    user_id creator;
    bool is_archived;
    bool is_general;
    std::vector<user_id> members;
    topic topic;
    purpose purpose;
    bool is_member;
    ts last_read;
    message latest;
    int64_t unread_count;
    int64_t unread_display_count;
};


//This is the data type that is returned from a slash command
struct command
{
    command() = default;

    command(const std::map<std::string, std::string> &params);

    std::string token; // gIkuvaNzQIHg97ATvDxqgjtO
    team_id team_id; // T0001
    std::string team_domain; // example
    channel_id channel_id; // C2147483705
    std::string channel_name; // test
    user_id user_id; // U2147483697
    std::string user_name; // Steve
    std::string command_name; // /weather
    std::string text; // 94070
    std::string response_url; // https://hooks.slack.com/commands/1234/5678
};


struct field
{
    template <class Json>
    operator Json();

    std::string title;
    std::string value;
    std::experimental::optional<bool> is_short; //because "short" is a keyword
};

struct attachment
{
    template <class Json>
    operator Json();

    std::experimental::optional<std::string> fallback;
    std::experimental::optional<std::string> color;
    std::experimental::optional<std::string> pretext;
    std::experimental::optional<std::string> author_name;
    std::experimental::optional<std::string> author_link;
    std::experimental::optional<std::string> author_icon;
    std::experimental::optional<std::string> title;
    std::experimental::optional<std::string> title_link;
    std::experimental::optional<std::string> text;
    std::experimental::optional<std::vector<field> > fields;
    std::experimental::optional<std::vector<std::string> > mrkdwn_in; //TODO shouldn't be strings
    std::experimental::optional<std::string> image_url;
    std::experimental::optional<std::string> thumb_url;
};


namespace incoming_webhook
{

namespace parameter
{

using channel_id = slack::channel_id;

MAKE_STRING_LIKE(username);

MAKE_BOOL_LIKE(mrkdwn);

MAKE_STRING_LIKE(icon_emoji);

using attachment = slack::attachment;

using attachments = std::vector<slack::attachment>;enum class response_type
{
    in_channel,
    ephemeral,
};
}

class payload
{
public:
    payload(const std::string &text);

    operator std::string();

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

    template<typename ...Os>
    static payload create_payload(const std::string &text)
    {
        return {text};
    }

    template<typename ...Os>
    static payload create_payload(const std::string &text, Os &&...os)
    {
        payload p{text};
        slack::set_option<decltype(p)>(p, std::forward<Os>(os)...);
        return p;
    }

private:

    std::string text_;
    std::experimental::optional<parameter::channel_id> channel_;
    std::experimental::optional<parameter::username> username_;
    std::experimental::optional<parameter::icon_emoji> icon_emoji_;
    std::experimental::optional<parameter::mrkdwn> mrkdwn_;
    std::experimental::optional<parameter::attachments> attachments_;
    std::experimental::optional<parameter::response_type> response_type_;
};

}

}