//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <string>


#define SLACK_FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)


namespace slack
{

using team_id = std::string; //for now
using user_id = std::string; //for now

}