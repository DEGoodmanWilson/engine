//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include <optional/optional.hpp>


#define SLACK_FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

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

    channel(const std::string &raw_json);

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

}