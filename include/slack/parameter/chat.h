//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/parameter/base.h>
#include <string>

namespace slack
{
namespace chat
{

// TODO Neither of these should be strictly string-like.

MAKE_STRING_LIKE(ts);

MAKE_STRING_LIKE(channel);

}
}