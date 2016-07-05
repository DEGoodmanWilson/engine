//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/chat.postMessage.h"
#include "private.h"
#include <json/json.h>

namespace slack { namespace chat
{

const std::string postMessage::error::MESSAGE_NOT_FOUND = std::string{"message_not_found"};
const std::string postMessage::error::CHANNEL_NOT_FOUND = std::string{"channel_not_found"};
const std::string postMessage::error::CANT_DELETE_MESSAGE = std::string{"cant_delete_message"};
const std::string postMessage::error::COMPLIANCE_EXPORTS_PREVENT_DELETION = std::string{"compliance_exports_prevent_deletion"};
const std::string postMessage::error::NOT_AUTHED = std::string{"not_authed"};
const std::string postMessage::error::INVALID_AUTH = std::string{"invalid_auth"};
const std::string postMessage::error::ACCOUNT_INACTIVE = std::string{"account_inactive"};


void postMessage::initialize_()
{
    http::params params{
            {"channel", channel_},
            {"text",    text_}
    };

    //optional parameters
    if (username_)
    {
        params.emplace("username", *username_);
    }
    if (as_user_)
    {
        params.emplace("as_user", (*as_user_ ? "true" : "false"));
    }
    if (parse_)
    {
        std::string parse_val{"none"};
        switch (*parse_)
        {
            case parameter::parse::none:
                parse_val = "none";
                break;
            case parameter::parse::full:
                parse_val = "full";
                break;
        }
        params.emplace("parse", parse_val);
    }
    if (link_names_)
    {
        params.emplace("link_names", (*link_names_ ? "true" : "false"));
    }
    if (attachments_)
    {
        //TODO this is ugly, but we need json strings.
        Json::Value root;
        for (auto &a : *attachments_)
        {
            root.append(a);
        }

        //TODO there is probably a better way?
        std::stringstream ss;
        ss << root;
        params.emplace("attachments", ss.str());
    }
    if (unfurl_links_)
    {
        params.emplace("unfurl_links", (*unfurl_links_ ? "true" : "false"));
    }
    if (unfurl_media_)
    {
        params.emplace("unfurl_media", (*unfurl_media_ ? "true" : "false"));
    }
    if (icon_url_)
    {
        params.emplace("icon_url", *icon_url_);
    }
    if (icon_emoji_)
    {
        params.emplace("icon_emoji", *icon_emoji_);
    }

    auto result_ob = slack_private::get(this, "chat.postMessage", params);
    if (!this->error_message)
    {
        if (result_ob["channel"].isString()) channel = slack::channel_id{result_ob["channel"].asString()};
        if (result_ob["ts"].isString()) ts = slack::ts{result_ob["ts"].asString()};
        if (result_ob["message"].isObject()) message = {result_ob["message"]};
    }
}

}} //namespace chat slack