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
namespace post_message
{

using channel_id = ::slack::channel_id;
MAKE_STRING_LIKE(text);
MAKE_STRING_LIKE(username);
MAKE_BOOL_LIKE(as_user);
enum class parse
{
    none = 0,
    full,
};
MAKE_BOOL_LIKE(link_names);
//This one needs to be better!!
MAKE_STRING_LIKE(attachments);
MAKE_BOOL_LIKE(unfurl_links);
MAKE_BOOL_LIKE(unfurl_media);
MAKE_STRING_LIKE(icon_url);
MAKE_STRING_LIKE(icon_emoji);

} //namespace post_message
} //namepsace parameter
} //namespace chat
} //namespace slack