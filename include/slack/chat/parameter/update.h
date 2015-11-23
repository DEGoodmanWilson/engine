//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/parameter/base.h>

namespace slack
{
namespace chat
{
namespace parameter
{
namespace update
{

using ts = ::slack::ts;
using channel_id = ::slack::channel_id;
MAKE_STRING_LIKE(text);
//This one needs to be better!!
MAKE_STRING_LIKE(attachments);
enum class parse
{
    none = 0,
    full,
};
MAKE_BOOL_LIKE(link_names);
} //namespace update
} //namepsace parameter
} //namespace chat
} //namespace slack