//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/attachment.h"
#include <json/json.h>

namespace slack { namespace attachment
{

field::field(const std::string &title, const std::string &value)
: title_{title}, value_{value}
{ }

template<>
field::operator Json::Value()
{
    Json::Value root;

    root["title"] = title_;
    root["value"] = value_;
    if (is_short_)
    {
        root["short"] = static_cast<bool>(*is_short_);
    }

    return root;
}

template<>
attachment::operator Json::Value()
{
    Json::Value root;

    if (fallback_) root["fallback"] = *fallback_;
    if (color_) root["color"] = *color_;
    if (pretext_) root["pretext"] = *pretext_;
    if (author_name_) root["author_name"] = *author_name_;
    if (author_link_) root["author_link"] = *author_link_;
    if (author_icon_) root["author_icon"] = *author_icon_;
    if (title_) root["title"] = *title_;
    if (title_link_) root["title_link"] = *title_link_;
    if (text_) root["text"] = *text_;
    if (fields_)
    {
        Json::Value fs;
        for (auto &f : *fields_)
        {
            fs.append(f);
        }
        root["fields"] = fs;
    }
    if (mrkdwn_in_)
    {

        Json::Value ms;
        for (auto m : *mrkdwn_in_)
        {
            std::string val;
            switch(m)
            {
                case parameter::mrkdwn_in_fields::text:
                    val = "text";
                    break;
                case parameter::mrkdwn_in_fields::pretext:
                    val = "pretext";
                    break;
                case parameter::mrkdwn_in_fields::fallback:
                    val = "fallback";
                    break;
            }
            ms.append(val);
        }
        root["mrkdwn_in"] = ms;
    }
    if (image_url_) root["image_url"] = *image_url_;
    if (thumb_url_) root["thumb_url"] = *thumb_url_;

    return root;
}

}}