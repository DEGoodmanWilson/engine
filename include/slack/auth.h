//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/macros.h>
#include <string>


namespace slack
{

namespace auth
{

class test_wrapper
{
public:
    test_wrapper() = default;

    api_response get_response();

private:

};

api_response test();


} //namespace auth
} //namespace slack