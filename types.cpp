//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/types.h"
#include "slack/set_option.h"
#include <json/json.h>
#include "uricodec.h"

namespace slack
{

//overload for our own json type. Clever way to get around exposing the json.h file in public interfaces. I hope.
template<>
channel::channel(const Json::Value &parsed_json) :
        id{parsed_json["id"].asString()},
        name{parsed_json["name"].asString()},
        is_channel{parsed_json["is_channel"].asBool()},
        created{parsed_json["created"].asInt()},
        creator{parsed_json["creator"].asString()},
        is_archived{parsed_json["is_archived"].asBool()},
        is_general{parsed_json["is_general"].asBool()},
        is_member{parsed_json["is_member"].asBool()},
        last_read{parsed_json["last_read"].asString()},
        unread_count{parsed_json["unread_count"].asInt()},
        unread_display_count{parsed_json["unread_display_count"].asInt()}
{
    for (const auto member_obj : parsed_json["members"])
    {
        members.emplace_back(member_obj.asString());
    }
    topic = {
            parsed_json["topic"]["value"].asString(),
            parsed_json["topic"]["creator"].asString(),
            parsed_json["topic"]["last_set"].asInt()
    };
    purpose = {
            parsed_json["purpose"]["value"].asString(),
            parsed_json["purpose"]["creator"].asString(),
            parsed_json["purpose"]["last_set"].asInt()
    };
}

template<>
message::message(const Json::Value &parsed_json)
{
    text = parsed_json["text"].asString();

    //TODO this needs more nuance.
    ts = parsed_json["ts"].asString();

    //TODO these are going to be optional probably
    username = parsed_json["username"].asString();
    type = parsed_json["type"].asString();
    if (!parsed_json["subtype"].isNull())
    {
        subtype = parsed_json["subtype"].asString();
    }
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
field::operator Json::Value()
{
    Json::Value root;

    root["title"] = title;
    root["value"] = value;
    if (is_short)
    {
        root["short"] = *is_short;
    }

    return root;
}

template<>
attachment::operator Json::Value()
{
    Json::Value root;

    if (fallback) root["fallback"] = *fallback;
    if (color) root["color"] = *color;
    if (pretext) root["pretext"] = *pretext;
    if (author_name) root["author_name"] = *author_name;
    if (author_link) root["author_link"] = *author_link;
    if (author_icon) root["author_icon"] = *author_icon;
    if (title) root["title"] = *title;
    if (title_link) root["title_link"] = *title_link;
    if (text) root["text"] = *text;
    if (fields)
    {
        Json::Value fs;
        for (auto &f : *fields)
        {
            fs.append(f);
        }
        root["fields"] = fs;
    }
    if (mrkdwn_in) {

        Json::Value ms;
        for (auto &m : *mrkdwn_in)
        {
            ms.append(m);
        }
        root["mrkdwn_in"] = ms;
    }
    if (image_url) root["image_url"] = *image_url;
    if (thumb_url) root["thumb_url"] = *thumb_url;

    return root;
}


namespace incoming_webhook
{

payload::payload(const parameter::text &text) : text_{text}
{ }

payload::payload(const parameter::attachments &attachments) : attachments_{attachments}
{ }

payload::operator std::string()
{
    Json::Value root;

    if (text_) root["text"] = *text_;
    if (channel_) root["channel"] = *channel_;
    if (username_) root["username"] = *username_;
    if (icon_emoji_) root["icon_emoji"] = *icon_emoji_;
    if (mrkdwn_) root["mrkdwn"] = *mrkdwn_ ? "true" : "false";
    if (response_type_)
    {
        std::string val{""};
        switch (*response_type_)
        {
            case parameter::response_type::in_channel:
                val = "in_channel";
                break;
            case parameter::response_type::ephemeral:
                val = "ephemeral";
        }
        root["response_type"] = val;
    }

    if (attachments_)
    {
        Json::Value as;
        for (auto &a : *attachments_)
        {
            as.append(a);
        }
        root["attachments"] = as;
    }

    //TODO there is probably a better way?
    std::stringstream ss;
    ss << root;
    return ss.str();
}


} //namespace incoming_webhook

} //namespace slack