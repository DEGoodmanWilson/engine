//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/chat.h"
#include "config.h"
#include <cpr.h>
#include <json/json.h>

namespace slack_config
{
extern std::string token_;
}

namespace slack
{
namespace chat
{
namespace impl
{

response::post_message post_message::get_response()
{
    cpr::Parameters params{
            {"token",   slack_config::token_},
            {"channel", channel_},
            {"text",    text_}
    };

    //optional parameters
    if (username_)
    {
        params.AddParameter({"username", *username_});
    }
    if (as_user_)
    {
        std::string val{"false"};
        if (static_cast<bool>(*as_user_)) val = "true";
        params.AddParameter({"as_user", val});
    }
    if (parse_)
    {
        std::string parse_val{"none"};
        if (*parse_ == parameter::post_message::parse::full)
            parse_val = "full";
        params.AddParameter({"parse", parse_val});
    }
    if (link_names_)
    {
        std::string val{"false"};
        if (static_cast<bool>(*link_names_)) val = "true";
        params.AddParameter({"link_names", val});
    }
    if (attachments_)
    {
        params.AddParameter({"attachments", *attachments_});
    }
    if (unfurl_links_)
    {
        std::string val{"false"};
        if (static_cast<bool>(*unfurl_links_)) val = "true";
        params.AddParameter({"unfurl_links", val});
    }
    if (unfurl_media_)
    {
        std::string val{"false"};
        if (static_cast<bool>(*unfurl_media_)) val = "true";
        params.AddParameter({"unfurl_media", val});
    }
    if (icon_url_)
    {
        params.AddParameter({"icon_url", *icon_url_});
    }
    if (icon_emoji_)
    {
        params.AddParameter({"icon_emoji", *icon_emoji_});
    }

    auto result = cpr::Get(cpr::Url{slack_config::HOSTNAME + "chat.postMessage"}, params);
    if (result.status_code != 200)
    {
        //error path
        return {result.text}; //TODO
    }

    return {result.text};
}


} //namespace impl
} //namespace chat
} //namespace slack
