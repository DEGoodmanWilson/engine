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

namespace slack
{
namespace api
{

/*************************************************************/
// MARK: - Parameters

namespace parameter
{
namespace test
{

MAKE_STRING_LIKE(error);

MAKE_STRING_LIKE(foo);

} //namespace test
} //namespace parameter

/*************************************************************/
// MARK: - Response Errors

namespace response
{
namespace error
{
namespace test
{

const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};

} //namespace test
} //namespace error
} //namespace response


/*************************************************************/
// MARK: - Response

namespace response
{

struct test :
        public slack::base::response
{
    test(const std::string &raw_json);

    std::experimental::optional<std::map<std::string, std::string>> args;
};

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

class test :
        public slack::base::impl<response::test>
{
public:
    //TODO can these be moved into the base class?
    response::test get_response();

    //TODO can we make a generic template?
    void set_option(const parameter::test::error &error)
    { error_ = error; }

    void set_option(parameter::test::error &&error)
    { error_ = std::move(error); }

    void set_option(const parameter::test::foo &foo)
    { foo_ = foo; }

    void set_option(parameter::test::foo &&foo)
    { foo_ = std::move(foo); }

private:
    std::experimental::optional<parameter::test::error> error_;
    std::experimental::optional<parameter::test::foo> foo_;
};

} //namespace impl


/*************************************************************/
// MARK: - Public Interface


template<typename ...Os>
response::test test()
{
    class impl::test impl;
    return impl.get_response();
}

template<typename ...Os>
response::test test(Os &&...os)
{
    class impl::test impl;
    set_option<decltype(impl)>(impl, std::forward<Os>(os)...);
    return impl.get_response();
}

} //namespace api
} //namespace slack