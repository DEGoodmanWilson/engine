//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/http.h>
#include <slack/config.h>
#include <string>
#include <map>

namespace slack
{
namespace config
{
const std::string HOSTNAME = "https://slack.com/api/";
}

namespace base
{

template<class T>
class impl
{
protected:
    T get(std::string endpoint, http::params params)
    {
        auto response = http::get(config::HOSTNAME+endpoint, params);
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