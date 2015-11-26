//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/rtm/response/start.h>
#include <slack/rtm/parameter/start.h>

namespace slack
{
namespace rtm
{
namespace impl
{

class start
{
public:

    start() = default;

    response::start get_response();


    void set_option(const parameter::start::simple_latest &simple_latest)
    { simple_latest_ = simple_latest; }
    void set_option(parameter::start::simple_latest &&simple_latest)
    { simple_latest_ = std::move(simple_latest); }

    void set_option(const parameter::start::no_unreads &no_unreads)
    { no_unreads_ = no_unreads; }
    void set_option(parameter::start::no_unreads &&no_unreads)
    { no_unreads_ = std::move(no_unreads); }

    void set_option(const parameter::start::mpim_aware &mpim_aware)
    { mpim_aware_ = mpim_aware; }
    void set_option(parameter::start::mpim_aware &&mpim_aware)
    { mpim_aware_ = std::move(mpim_aware); }

private:
    std::experimental::optional<parameter::start::simple_latest> simple_latest_;
    std::experimental::optional<parameter::start::no_unreads> no_unreads_;
    std::experimental::optional<parameter::start::mpim_aware> mpim_aware_;
};

} //namespace impl
} //namespace rtm
} //namespace slack