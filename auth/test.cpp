//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/auth.h"
#include "config.h"
#include <cpr.h>
#include <json/json.h>

namespace slack
{

namespace auth
{

response::test test()
{
    impl::test impl;
    return impl.get_response();
}

} //namespace auth
} //namespace slack