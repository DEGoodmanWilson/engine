//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/parameter/base.h>
#include <string>

namespace slack
{
namespace api
{

class error :
        public std::string
{
public:
    error() = default;

    error(const error &rhs) = default;

    error(error &&rhs) = default;

    error &operator=(const error &rhs) = default;

    error &operator=(error &&rhs) = default;

    explicit error(const char *raw_string) : std::string(raw_string)
    { }

    explicit error(const char *raw_string, size_t length) : std::string(raw_string, length)
    { }

    explicit error(size_t to_fill, char character) : std::string(to_fill, character)
    { }

    explicit error(const std::string &std_string) : std::string(std_string)
    { }

    explicit error(const std::string &std_string, size_t position, size_t length = std::string::npos)
            : std::string(std_string, position, length)
    { }

    explicit error(std::initializer_list<char> il) : std::string(il)
    { }

    template<class InputIterator>
    explicit error(InputIterator first, InputIterator last)
            : std::string(first, last)
    { }
};


class foo :
        public std::string
{
public:
    foo() = default;

    foo(const foo &rhs) = default;

    foo(foo &&rhs) = default;

    foo &operator=(const foo &rhs) = default;

    foo &operator=(foo &&rhs) = default;

    explicit foo(const char *raw_string) : std::string(raw_string)
    { }

    explicit foo(const char *raw_string, size_t length) : std::string(raw_string, length)
    { }

    explicit foo(size_t to_fill, char character) : std::string(to_fill, character)
    { }

    explicit foo(const std::string &std_string) : std::string(std_string)
    { }

    explicit foo(const std::string &std_string, size_t position, size_t length = std::string::npos)
            : std::string(std_string, position, length)
    { }

    explicit foo(std::initializer_list<char> il) : std::string(il)
    { }

    template<class InputIterator>
    explicit foo(InputIterator first, InputIterator last)
            : std::string(first, last)
    { }
};
}
}