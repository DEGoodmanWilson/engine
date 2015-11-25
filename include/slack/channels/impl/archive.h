//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/channels/response/archive.h>
#include <slack/channels/parameter/archive.h>

namespace slack
{
namespace channels
{
namespace impl
{

class archive
{
public:
    archive(const channel_id& channel) : channel_{channel} {}

    response::archive get_response();
private:
    channel_id channel_;
};

} //namespace impl
} //namespace channels
} //namespace slack