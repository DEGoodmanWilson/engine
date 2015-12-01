//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/rtm.start.h"
#include "private.h"

namespace slack
{
namespace rtm
{


/*************************************************************/
// MARK: - Response

namespace response
{

start::start(const std::string &raw_json)
        : slack::base::response{raw_json}
{
    Json::Value result_ob = json_->json;

    if (result_ob["url"].isString()) url = result_ob["url"].asString();

    if (!result_ob["channels"].isNull() && result_ob["channels"].isArray())
    {
        channels = std::vector<::slack::channel>{};
        for (const auto channel_obj : result_ob["channels"])
        {
            channels->emplace_back(channel_obj);
        }
    }

    //TODO: There is a lot of work left to be done here!

}

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

response::start start::get_response()
{
    http::params params;

    //optional parameters
    if (simple_latest_)
    {
        params.emplace("simple_latest", (*simple_latest_ ? "true" : "false"));
    }
    if (no_unreads_)
    {
        params.emplace("no_unreads", (*no_unreads_ ? "true" : "false"));
    }
    if (mpim_aware_)
    {
        params.emplace("mpim_aware", (*mpim_aware_ ? "true" : "false"));
    }

    return get("rtm.start", params);
}

} //namespace impl
} //namespace channel
} //namespace slack