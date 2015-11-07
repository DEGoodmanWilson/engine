//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include "types.h"
#include <string>


namespace slack
{
    class auth
    {
    public:
        api_response test() const;
    };

//syntactic sugar:
static auth auth;

} //namespace slack