//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <string>


namespace slack
{
    class auth
    {
    public:
        std::string test();
    };

//syntactic sugar:
static auth auth;

} //namespace slack