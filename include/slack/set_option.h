//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/fwd.h>

namespace slack
{

template<typename I, typename O>
void set_option(I &impl, O &&o)
{
    impl.set_option(SLACK_FWD(o));

}

template<typename I, typename O, typename... Os>
void set_option(I &impl, O &&o, Os &&... os)
{
    set_option(impl, SLACK_FWD(o));
    set_option(impl, SLACK_FWD(os)...);
}

}