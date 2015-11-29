//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/api/test.h>
#include <slack/base/impl.h>

namespace slack
{
namespace api
{
namespace impl
{



class test :
        public slack::base::impl<slack::api::response::test>
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
} //namespace api
} //namespace slack