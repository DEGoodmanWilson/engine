//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/types.h"
#include "slack/set_option.h"
#include <json/json.h>
#include "uricodec.h"

namespace slack
{

template<>
profile::profile(const Json::Value &parsed_json)
{
    //TODO Better error checking!!!
    first_name = parsed_json["first_name"].asString();
    last_name = parsed_json["last_name"].asString();
    real_name = parsed_json["real_name"].asString();
    email = parsed_json["email"].asString();
    skype = parsed_json["skype"].asString();
    phone = parsed_json["phone"].asString();
    images[24] = parsed_json["image_24"].asString();
    images[32] = parsed_json["image_24"].asString();
    images[48] = parsed_json["image_24"].asString();
    images[72] = parsed_json["image_24"].asString();
    images[192] = parsed_json["image_24"].asString();
    if(parsed_json["bot_id"].isString())
    {
        bot_id = {parsed_json["bot_id"].asString()};
    }
    if(parsed_json["api_app_id"].isString())
    {
        api_app_id = {parsed_json["api_app_id"].asString()};
    }
}

template<>
user::user(const Json::Value &parsed_json)
{
    id = parsed_json["id"].asString();
    name = parsed_json["name"].asString();
    deleted = parsed_json["deleted"].asBool();
    color = parsed_json["color"].asString();
    profile = {parsed_json["profile"]};
    is_admin = parsed_json["is_admin"].asBool();
    is_onwer = parsed_json["is_onwer"].asBool();
    has_2fa = parsed_json["has_2fa"].asBool();
    has_files = parsed_json["has_files"].asBool();

}


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
    for (auto u: parsed_json["users"])
    {
        users.emplace_back(user_id{u.asString()});
    }
}

template<>
message::message(const Json::Value &parsed_json)
{
    channel = channel_id{parsed_json["channel"].asString()};
    user = user_id{parsed_json["user"].asString()};
    text = parsed_json["text"].asString();
    ts = slack::ts{parsed_json["ts"].asString()};
    is_starred = (parsed_json["is_starred"].isString()) ? parsed_json["is_starred"].asBool() : false;
    if (parsed_json["pinned_to"].isArray())
    {
        for (auto p: parsed_json["pinned_to"])
        {
            pinned_to.emplace_back(channel_id{p.asString()});
        }
    }
    if (parsed_json["reactions"].isArray())
    {
        for (auto r: parsed_json["reactions"])
        {
            reactions.emplace_back(reaction{r});
        }
    }
}

} //namespace slack