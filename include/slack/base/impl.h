//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/http.h>
#include <string>
#include <map>

namespace slack
{
namespace base
{

template<class T>
class impl
{
protected:
    T get(std::string url, http::params params)
    {
        auto response = http::get(url, params);
        if(response.status_code != 200)
        {
            //TODO do something!
            return {response.body};
        }

        return {response.body};
    }
};

} //namespace base
} //namespace slack