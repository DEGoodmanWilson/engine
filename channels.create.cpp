//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/channels.create.h"
#include "private.h"

namespace slack
{
namespace channels
{


/*************************************************************/
// MARK: - Response

namespace response
{

create::create(const std::string &raw_json)
        : slack::base::response{raw_json}
{
    Json::Value result_ob = json_->json;

//    The inability to say the following vexes me:
//    if (result_ob["channel"].isObject()) channel = slack::channel{result_ob["channel"]};
    if (result_ob["channel"].isObject()) channel = slack::channel(result_ob["channel"]);

}

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

create::create(const std::string &name) : name_{name}
{ }

response::create create::get_response()
{
    http::params params{{"name", name_}};

    return get("channels.create", params);
}

} //namespace impl


/*************************************************************/
// MARK: - Public Interface

::slack::channels::response::create create(const std::string &name)
{
    class impl::create impl{name};
    return impl.get_response();
}

} //namespace channel
} //namespace slack