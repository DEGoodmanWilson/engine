//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <utility>

#define SLACK_FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)