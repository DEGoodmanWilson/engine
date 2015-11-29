//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <memory>

namespace slack
{

namespace priv
{
struct param_impl;
}

namespace base
{

template<class T>
class impl
{
protected:
    T handle_response(uint32_t response_code, const std::string& response_body)
    {
        //TODO can we roll the call to GET in here too!?
        if (response_code != 200)
        {
            //error path
            return {response_body};
        }

        return {response_body};
    }
};

} //namespace base
} //namespace slack