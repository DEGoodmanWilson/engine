//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/oauth.access.h"
#include "private.h"

namespace slack
{
namespace oauth
{


/*************************************************************/
// MARK: - Response

namespace response
{

access::access(const std::string &raw_json)
        : slack::base::response{raw_json}
{
    if(!json_) return;

    Json::Value result_ob = json_->json;

    if (result_ob["access_token"].isString()) access_token = {result_ob["access_token"].asString()};
    if (result_ob["scope"].isString()) scope = {result_ob["scope"].asString()};
}

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

access::access(const std::string &client_id, const std::string &client_secret, const std::string &code) :
        client_id_{client_id}, client_secret_{client_secret}, code_{code}
{ }

response::access access::get_response()
{
    http::params params{
            {"client_id",     client_id_},
            {"client_secret", client_secret_},
            {"code",          code_}
    };

    if (redirect_uri_)
    {
        params.emplace("redirect_uri", *redirect_uri_);
    }

    return get("oauth.access", params);
}

} //namespace impl


} //namespace channel
} //namespace slack