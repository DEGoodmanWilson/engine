//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <string>
#include <slack/set_option.h>
#include <slack/web/oauth.access.h>
#include <slack/base/slack_delegate.h>

namespace slack
{

namespace containers
{
class oauth
{
public:
    oauth(slack_delegate *delegate) : delegate_{delegate}
    {}

    template<class CLIENT_ID, class CLIENT_SECRET, class CODE, typename ...Os>
    ::slack::oauth::access access(CLIENT_ID &&client_id,
                                  CLIENT_SECRET &&client_secret,
                                  CODE &&code) const
    {
        return ::slack::oauth::access{delegate_->token(),
                                      std::forward<CLIENT_ID>(client_id),
                                      std::forward<CLIENT_SECRET>(client_secret),
                                      std::forward<CODE>(code)};
    }

    template<class CLIENT_ID, class CLIENT_SECRET, class CODE, typename ...Os>
    ::slack::oauth::access access(CLIENT_ID &&client_id,
                                  CLIENT_SECRET &&client_secret,
                                  CODE &&code,
                                  Os &&...os) const
    {
        return ::slack::oauth::access{delegate_->token(),
                                      std::forward<CLIENT_ID>(client_id),
                                      std::forward<CLIENT_SECRET>(client_secret),
                                      std::forward<CODE>(code),
                                      SLACK_FWD(os)...};
    }

private:
    const slack_delegate *delegate_;
};
} //namespace endpoints
} //namespace slack