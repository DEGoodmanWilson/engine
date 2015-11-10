//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <string>

#define MAKE_STRING_LIKE(x) class x : public std::string \
{ \
public: \
    x() = default; \
        x(const x &rhs) = default; \
        x(x &&rhs) = default; \
        x &operator=(const x &rhs) = default; \
        x &operator=(x &&rhs) = default; \
        explicit x(const char *raw_string) : std::string(raw_string) {} \
        explicit x(const char *raw_string, size_t length) : std::string(raw_string, length) {} \
        explicit x(size_t to_fill, char character) : std::string(to_fill, character) {} \
        explicit x(const std::string &std_string) : std::string(std_string) {} \
        explicit x(const std::string &std_string, size_t position, size_t length = std::string::npos) \
            : std::string(std_string, position, length) {} \
        explicit x(std::initializer_list<char> il) : std::string(il) {} \
        template<class InputIterator> \
    explicit x(InputIterator first, InputIterator last) \
            : std::string(first, last) {} \
};

namespace slack
{



}