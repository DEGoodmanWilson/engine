//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/channels/response/create.h>
#include <slack/channels/parameter/create.h>

namespace slack
{
namespace channels
{
namespace impl
{

class create
{
public:
    create(const std::string &name) : name_{name}
    { }

    response::create get_response();

private:
    std::string name_;
};

} //namespace impl
} //namespace channels
} //namespace slack