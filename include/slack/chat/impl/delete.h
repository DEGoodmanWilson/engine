//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/chat/response/delete.h>
#include <slack/chat/parameter/delete.h>

namespace slack
{
namespace chat
{
namespace impl
{

class delete_it
{
public:
    delete_it(const ts &ts, const channel_id channel) :
            ts_{ts}, channel_{channel}
    { }

    response::delete_it get_response();

private:
    ts ts_;
    channel_id channel_;

};

} //namespace impl
} //namespace chat
} //namespace slack