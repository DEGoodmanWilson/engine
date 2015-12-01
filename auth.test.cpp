//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/auth.test.h"
#include "slack/http.h"
#include "private.h"
#include <json/json.h>

namespace slack
{
namespace auth
{


/*************************************************************/
// MARK: - Response

namespace response
{

test::test(const std::string &raw_json)
        : slack::base::response{raw_json}
{
    if(!json_) return;

    Json::Value result_ob = json_->json;

    if (result_ob["url"].isString()) url = result_ob["url"].asString();
    if (result_ob["team"].isString()) teamname = result_ob["team"].asString();
    if (result_ob["user"].isString()) username = result_ob["user"].asString();
    if (result_ob["team_id"].isString()) team_id = slack::team_id{result_ob["team_id"].asString()};
    if (result_ob["user_id"].isString()) user_id = slack::user_id{result_ob["user_id"].asString()};
}

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

response::test test::get_response()
{
    return get("auth.test", {});
}

} //namespace impl


/*************************************************************/
// MARK: - Public Interface

::slack::auth::response::test test()
{
    class impl::test impl;
    return impl.get_response();
}


} //namespace auth
} //namespace slack