//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/chat.h"
#include "config.h"
#include <cpr.h>
#include <json/json.h>

namespace slack
{

namespace chat
{

response::delete_it delete_it(parameter::delete_it::ts ts, parameter::delete_it::channel_id channel)
{
    impl::delete_it impl{ts, channel};
    return impl.get_response();
}

} //namespace chat
} //namespace slack