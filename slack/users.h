//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <string>
#include <slack/set_option.h>
#include <slack/web/users.list.h>
#include <slack/web/users.info.h>
#include <slack/base/slack_delegate.h>

namespace slack
{

namespace containers
{
class users
{
public:
    users(slack_delegate *delegate) : delegate_{delegate}
    {}

    template<typename ...Os>
    ::slack::users::list list() const
    {
        return ::slack::users::list{delegate_->token()};
    }

    template<typename ...Os>
    ::slack::users::list list(Os &&...os) const
    {
        return ::slack::users::list{delegate_->token(), SLACK_FWD(os)...};
    }

    template<class USER_ID>
    ::slack::users::info info(USER_ID &&user) const
    {
        return ::slack::users::info{delegate_->token(), std::forward<USER_ID>(user)};
    }

private:
    const slack_delegate *delegate_;
};
} //namespace endpoints
} //namespace slack