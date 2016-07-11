//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <slack/fwd.h>

namespace slack
{

template<class S, typename T>
void set_option(S &session, T &&t)
{
    session.set_option(SLACK_FWD(t));
}

template<class S, typename T, typename... Ts>
void set_option(S &session, T &&t, Ts &&... ts)
{
    set_option(session, SLACK_FWD(t));
    set_option(session, SLACK_FWD(ts)...);
}
} //namespace engin