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

using ts = ::slack::ts;
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

}
}