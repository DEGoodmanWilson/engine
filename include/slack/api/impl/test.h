//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/api/test.h>

namespace slack
{
namespace api
{
namespace impl
{

class test
{
public:
    test() = default;

    response::test get_response();

    void set_option(const parameter::test::error &error)
    { error_ = error; }

    void set_option(parameter::test::error &&error)
    { error_ = std::move(error); }

    void set_option(const parameter::test::foo &foo)
    { foo_ = foo; }

    void set_option(parameter::test::foo &&foo)
    { foo_ = std::move(foo); }

private:
    parameter::test::error error_;
    parameter::test::foo foo_;
};

} //namespace impl
} //namespace api
} //namespace slack