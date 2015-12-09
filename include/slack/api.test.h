//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <slack/base/impl.h>
#include <map>
#include <string>
#include <slack/optional.hpp>

namespace slack { namespace api
{

class test :
        public slack::base::response
{
public:
    //public interface
    test(const test &other) = default;
    test(test &&other) = default;
    test(test &other)
            : test(const_cast<const test &>(other))
    { }

    template<typename ...Os>
    test()
    {
        initialize_();
    }

    template<typename ...Os>
    test(Os &&...os)
    {
        slack::set_option<test>(*this, std::forward<Os>(os)...);
        initialize_();
    }

    //parameters
    struct parameter
    {
        MAKE_STRING_LIKE(error);

        MAKE_STRING_LIKE(foo);
    };

    //errors
    struct error :
            public slack::base::error
    {
    };

    //response
    std::experimental::optional<std::map<std::string, std::string>> args;

    //parameter setters
    void set_option(const parameter::error &error)
    { error_ = error; }

    void set_option(parameter::error &&error)
    { error_ = std::move(error); }

    void set_option(const parameter::foo &foo)
    { foo_ = foo; }

    void set_option(parameter::foo &&foo)
    { foo_ = std::move(foo); }

private:
    void initialize_();

    std::experimental::optional<parameter::error> error_;
    std::experimental::optional<parameter::foo> foo_;
};

}} //namespace api slack