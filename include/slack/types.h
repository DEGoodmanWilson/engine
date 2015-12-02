//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include <map>
#include <slack/optional.hpp>

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

}