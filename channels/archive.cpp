//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/channels.h"
#include "config.h"
#include <cpr.h>
#include <json/json.h>

namespace slack
{

namespace channels
{

response::archive archive(const channel_id& channel)
{
    class impl::archive impl{channel};
    return impl.get_response();
}

} //namespace channels
} //namespace slack

