//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/channels/response/list.h>
#include <slack/channels/parameter/list.h>

namespace slack
{
namespace channels
{
namespace impl
{

class list
{
public:
    list() = default;

    response::list get_response();

    void set_option(parameter::exclude_archived exclude_archived)
    { *exclude_archived_ = exclude_archived; }

private:
    std::experimental::optional<parameter::exclude_archived> exclude_archived_;
};

} //namespace impl
} //namespace channels
} //namespace slack