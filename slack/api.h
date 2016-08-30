//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <string>
#include <slack/set_option.h>
#include <slack/web/api.test.h>
#include <slack/base/slack_delegate.h>

namespace slack
{

namespace containers
{
class api
{
public:
    api(slack_delegate *delegate) : delegate_{delegate}
    { }

    template<typename ...Os>
    ::slack::api::test test() const
    {
        return ::slack::api::test{};
    }

    template<typename ...Os>
    ::slack::api::test test(Os &&...os) const
    {
        return ::slack::api::test{SLACK_FWD(os)...};
    }

private:
    const slack_delegate *delegate_;
};
} //namespace endpoints
} //namespace slack