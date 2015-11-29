//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <memory>

namespace slack
{
namespace base
{

template<class T>
class impl
{
protected:
    T handle_response(uint32_t response_code, const std::string& response_body)
    {
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