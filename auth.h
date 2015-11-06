//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include "api_base.h"
#include <string>


namespace slack
{
    class auth : api_base
    {
    public:
        auth(plaid *delegate) : api_base(delegate)
        { }

        std::string test();
    };

} //namespace slack