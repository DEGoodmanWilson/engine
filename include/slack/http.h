//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <string>
#include <map>
#include <functional>

namespace slack
{
namespace http
{

struct response
{
    uint32_t status_code;
    //TODO other error codes here.
    std::string body;
};

using params = std::map<std::string, std::string>;

extern std::function<response(std::string url, params)> get;
extern std::function<response(std::string url, params)> post;

} //namespace http
} //namespace slack