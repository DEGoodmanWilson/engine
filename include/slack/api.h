//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/response/api.h>
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


class test_wrapper
{
public:
    test_wrapper() = default;

    ::slack::response::api::test get_response();

    void set_option(const error &error)
    { error_ = error; }

    void set_option(error &&error)
    { error_ = std::move(error); }

    void set_option(const foo &foo)
    { foo_ = foo; }

    void set_option(foo &&foo)
    { foo_ = std::move(foo); }

private:
    error error_;
    foo foo_;
};


template<typename T>
void set_option(test_wrapper &wrapper, T &&t)
{
    wrapper.set_option(SLACK_FWD(t));
}

template<typename T, typename... Ts>
void set_option(test_wrapper &wrapper, T &&t, Ts &&... ts)
{
    set_option(wrapper, SLACK_FWD(t));
    set_option(wrapper, SLACK_FWD(ts)...);
}

template<typename ...Ts>
::slack::response::api::test test()
{
    class test_wrapper wrapper;
    return wrapper.get_response();
}

template<typename ...Ts>
::slack::response::api::test test(Ts &&...ts)
{
    class test_wrapper wrapper;
    set_option(wrapper, std::forward<Ts>(ts)...);
    return wrapper.get_response();
}



} //namespace api
} //namespace slack