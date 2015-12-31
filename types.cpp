//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/types.h"
#include "slack/set_option.h"
#include <json/json.h>
#include "uricodec.h"

namespace slack
{

command::command(const std::map<std::string, std::string> &params)
{
    if (params.count("token")) token = UriDecode(params.at("token"));
    if (params.count("team_id")) team_id = UriDecode(params.at("team_id"));
    if (params.count("team_domain")) team_domain = UriDecode(params.at("team_domain"));
    if (params.count("channel_id")) channel_id = UriDecode(params.at("channel_id"));
    if (params.count("channel_name")) channel_name = UriDecode(params.at("channel_name"));
    if (params.count("user_id")) user_id = UriDecode(params.at("user_id"));
    if (params.count("user_name")) user_name = UriDecode(params.at("user_name"));
    if (params.count("command")) command_name = UriDecode(params.at("command"));
    if (params.count("text")) text = UriDecode(params.at("text"));
    if (params.count("response_url")) response_url = UriDecode(params.at("response_url"));
}

template<>
reaction::reaction(const Json::Value &parsed_json)
{
    name = parsed_json["name"].asString();
    count = parsed_json["count"].asInt64();
    for(auto u: parsed_json["users"])
    {
        users.emplace_back(user_id{u.asString()});
    }
}

} //namespace slack