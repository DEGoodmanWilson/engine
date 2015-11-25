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

response::create create(const std::string& name)
{
    class impl::create impl{name};
    return impl.get_response();
}

} //namespace channels
} //namespace slack

