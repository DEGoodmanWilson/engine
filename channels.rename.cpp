//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/channels.rename.h"
#include "private.h"

namespace slack
{
namespace channels
{


/*************************************************************/
// MARK: - Response

namespace response
{

rename::rename(const std::string &raw_json)
        : slack::base::response{raw_json}
{
    if(!json_) return;

    Json::Value result_ob = json_->json;

//    The inability to say the following vexes me:
//    if (result_ob["channel"].isObject()) channel = slack::channel{result_ob["channel"]};
    if (result_ob["channel"].isObject()) channel = slack::channel{result_ob["channel"]};

}

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

rename::rename(const channel_id& channel, const std::string& name) : channel_{channel}, name_{name}
{ }

response::rename rename::get_response()
{
    http::params params{
            {"channel", channel_},
            {"name", name_}
    };

    return get("channels.rename", params);
}

} //namespace impl


/*************************************************************/
// MARK: - Public Interface

::slack::channels::response::rename rename(const channel_id& channel, const std::string& name)
{
    class impl::rename impl{channel, name};
    return impl.get_response();
}

} //namespace channel
} //namespace slack