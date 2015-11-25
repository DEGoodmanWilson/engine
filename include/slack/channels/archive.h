//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/channels/parameter/archive.h>
#include <slack/channels/response/archive.h>
#include <slack/channels/impl/archive.h>

namespace slack
{
namespace channels
{

response::archive archive(const channel_id& channel);

} //namespace channels
} //namespace slack