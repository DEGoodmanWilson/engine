//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/http.h"

namespace slack
{
namespace http
{

std::function<response(std::string url, params)> get;
std::function<response(std::string url, params)> post;

} //namespace http
} //namespace slack
