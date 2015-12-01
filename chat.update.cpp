//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/chat.update.h"
#include "private.h"

namespace slack
{
namespace chat
{


/*************************************************************/
// MARK: - Response

namespace response
{

update::update(const std::string &raw_json)
        : slack::base::response{raw_json}
{
    if(!json_) return;

    Json::Value result_ob = json_->json;

    if (result_ob["channel"].isString()) channel = slack::channel_id{result_ob["channel"].asString()};
    if (result_ob["ts"].isString()) ts = slack::ts{result_ob["ts"].asString()};
    if (result_ob["text"].isString()) text = result_ob["text"].asString();
}

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

update::update(const ts &ts, const channel_id &channel, const std::string &text) : ts_{ts}, channel_{channel}, text_{text}
{ }

response::update update::get_response()
{
    http::params params{
            {"ts", ts_},
            {"channel", channel_},
            {"text",    text_}
    };

    //optional parameters
    if (parse_)
    {
        std::string parse_val{"none"};
        switch (*parse_)
        {
            case parameter::update::parse::none:
                parse_val = "none";
                break;
            case parameter::update::parse::full:
                parse_val = "full";
                break;
        }
        params.emplace("parse", parse_val);
    }
    if (link_names_)
    {
        params.emplace("link_names", (*link_names_ ? "true" : "false"));
    }
    if (attachments_)
    {
        params.emplace("attachments", *attachments_);
    }

    return get("chat.update", params);
}

} //namespace impl


/*************************************************************/
// MARK: - Public Interface


response::update update(const ts &ts, const channel_id &channel, const std::string &text)
{
    class impl::update impl{ts, channel, text};
    return impl.get_response();
}

} //namespace channel
} //namespace slack