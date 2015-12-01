//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/chat.delete.h"
#include "private.h"

namespace slack
{
namespace chat
{


/*************************************************************/
// MARK: - Response

namespace response
{

delete_it::delete_it(const std::string &raw_json)
        : slack::base::response{raw_json}
{
    Json::Value result_ob = json_->json;

    if (result_ob["channel"].isObject()) channel = slack::channel_id{result_ob["channel"].asString()};
    if (result_ob["ts"].isObject()) ts = slack::ts{result_ob["ts"].asString()};

}

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

delete_it::delete_it(const ts &ts, const channel_id &channel) : ts_{ts}, channel_{channel}
{ }

response::delete_it delete_it::get_response()
{
    http::params params{
            {"ts",      ts_},
            {"channel", channel_}
    };

    return get("chat.delete_it", params);
}

} //namespace impl


/*************************************************************/
// MARK: - Public Interface


response::delete_it delete_it(const ts &ts, const channel_id &channel)
{
    class impl::delete_it impl{ts, channel};
    return impl.get_response();
}

} //namespace channel
} //namespace slack