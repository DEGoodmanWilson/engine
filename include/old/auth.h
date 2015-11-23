//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/response/auth.h>
#include <string>


namespace slack
{


namespace auth
{



class test_wrapper
{
public:
    test_wrapper() = default;

    ::slack::response::auth::test get_response();

private:

};

::slack::response::auth::test test();


} //namespace auth
} //namespace slack