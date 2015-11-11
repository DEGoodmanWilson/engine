//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <string>


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
};

namespace slack
{

//TODO NONE of these things should be just strings.

MAKE_STRING_LIKE(team_id);
MAKE_STRING_LIKE(user_id);
MAKE_STRING_LIKE(ts);
MAKE_STRING_LIKE(channel);

}