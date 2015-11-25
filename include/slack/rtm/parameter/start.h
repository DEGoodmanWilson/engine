//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/parameter/base.h>

namespace slack
{
namespace rtm
{
namespace parameter
{
namespace start
{

MAKE_BOOL_LIKE(simple_latest);
MAKE_BOOL_LIKE(no_unreads);
MAKE_BOOL_LIKE(mpim_aware);

} //namespace start
} //namepsace parameter
} //namespace rtm
} //namespace slack