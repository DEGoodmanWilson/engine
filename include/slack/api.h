//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include "types.h"
#include <string>


namespace slack
{
class api
{
public:
    api_response test(const std::string &error = "", const std::string &foo = "") const;
};

//syntactic sugar:
static api api;

} //namespace slack