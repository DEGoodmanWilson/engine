//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <string>


#define CPR_FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)


namespace slack
{
using api_response = std::string;
}