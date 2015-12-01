//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/chat.post_message.h"
#include "private.h"

namespace slack
{
namespace chat
{


/*************************************************************/
// MARK: - Response

namespace response
{

post_message::post_message(const std::string &raw_json)
        : slack::base::response{raw_json}
{
    Json::Value result_ob = json_->json;

    if (result_ob["channel"].isObject()) channel = slack::channel_id{result_ob["channel"].asString()};
    if (result_ob["ts"].isObject()) ts = slack::ts{result_ob["ts"].asString()};

}

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

post_message::post_message(const channel_id &channel, const std::string &text) : channel_{channel}, text_{text}
{ }

response::post_message post_message::get_response()
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
            case parameter::post_message::parse::none:
                parse_val = "none";
                break;
            case parameter::post_message::parse::full:
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
        params.emplace("attachments", *attachments_);
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

    return get("chat.post_message", params);
}

} //namespace impl

/*************************************************************/
// MARK: - Public Interface


response::post_message post_message(const ts &ts, const channel_id channel)
{
    class impl::post_message impl{ts, channel};
    return impl.get_response();
}

} //namespace channel
} //namespace slack