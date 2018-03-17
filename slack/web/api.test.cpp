//
// engine
//
// Copyright © 2017 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/web/api.test.h"
#include "private.h"

#include <iostream>

namespace slack { namespace api
{


void test::initialize_()
{
            
    auto params = default_params({
    });

    //optional parameters
    if(error_)
    {
        params.emplace("error", *error_);
    }
    if(foo_)
    {
        params.emplace("foo", *foo_);
    }

    auto result_ob = slack_private::get(this, "api.test", params);

    if(this->success())
    {
        if(result_ob["args"].isObject())
        {
            for (auto arg: result_ob["args"].getMemberNames())
            {
                args.emplace(arg, result_ob["args"][arg].asString());
            }
        }
    }
}

}} //namespace api slack