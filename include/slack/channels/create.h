//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/channels/parameter/create.h>
#include <slack/channels/response/create.h>
#include <slack/channels/impl/create.h>

namespace slack
{
namespace channels
{

response::create create(const std::string& name);

} //namespace channels
} //namespace slack