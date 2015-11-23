//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/chat/parameter/delete.h>
#include <slack/chat/response/delete.h>
#include <slack/chat/impl/delete.h>

namespace slack
{
namespace chat
{

response::delete_it delete_it(parameter::delete_it::ts ts, parameter::delete_it::channel_id channel);

} //namespace chat
} //namespace slack