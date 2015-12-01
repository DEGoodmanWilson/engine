//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/channels.archive.h"
#include "private.h"

namespace slack
{
namespace channels
{


/*************************************************************/
// MARK: - Response

namespace response
{

archive::archive(const std::string &raw_json)
        : slack::base::response{raw_json}
{
    if(!json_) return;

    Json::Value result_ob = json_->json;
}

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

archive::archive(const channel_id &channel) : channel_{}
{ }

response::archive archive::get_response()
{
    http::params params{{"channel", channel_}};

    return get("channels.archive", params);
}

} //namespace impl


/*************************************************************/
// MARK: - Public Interface

::slack::channels::response::archive archive(const channel_id &channel)
{
    class impl::archive impl{channel};
    return impl.get_response();
}

} //namespace channel
} //namespace slack