//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/incoming_webhook.h"
#include <json/json.h>

namespace slack { namespace incoming_webhook
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


}} //namespace incoming_webhook