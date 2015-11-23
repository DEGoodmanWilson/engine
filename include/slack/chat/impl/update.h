//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/chat/response/update.h>
#include <slack/chat/parameter/update.h>

namespace slack
{
namespace chat
{
namespace impl
{

class update
{
public:

    update(const parameter::update::ts &ts, const parameter::update::channel_id &channel, const parameter::update::text &text) :
            ts_{ts}, channel_{channel}, text_{text}
    { }

    response::update get_response();


    void set_option(const parameter::update::parse &parse)
    { parse_ = parse; }

    void set_option(parameter::update::parse &&parse)
    { parse_ = std::move(parse); }

    void set_option(const parameter::update::link_names &link_names)
    { link_names_ = link_names; }

    void set_option(parameter::update::link_names &&link_names)
    { link_names_ = std::move(link_names); }

    void set_option(const parameter::update::attachments &attachments)
    { attachments_ = attachments; }

    void set_option(parameter::update::attachments &&attachments)
    { attachments_ = std::move(attachments); }

private:
    parameter::update::ts ts_;
    parameter::update::channel_id channel_;
    parameter::update::text text_;
    std::experimental::optional<parameter::update::attachments> attachments_;
    std::experimental::optional<parameter::update::parse> parse_;
    std::experimental::optional<parameter::update::link_names> link_names_;
};

} //namespace impl
} //namespace chat
} //namespace slack