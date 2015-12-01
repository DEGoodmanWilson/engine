//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/channels.list.h"
#include "slack/http.h"
#include "private.h"
#include <json/json.h>

namespace slack
{
namespace channels
{


/*************************************************************/
// MARK: - Response

namespace response
{

list::list(const std::string &raw_json)
        : slack::base::response{raw_json}
{
    if(!json_) return;

    Json::Value result_ob = json_->json;

    if (!result_ob["channels"].isNull() && result_ob["channels"].isArray())
    {
        channels = std::vector<::slack::channel>{};
        for (const auto channel_obj : result_ob["channels"])
        {
            channels->emplace_back(channel_obj);
        }
    }
}

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

response::list list::get_response()
{
    http::params params;

    if (exclude_archived_)
    {
        params.emplace("exclude_archived", (*exclude_archived_ ? "true" : "false"));
    }

    return get("channels.list", params);
}

} //namespace impl
} //namespace channel
} //namespace slack