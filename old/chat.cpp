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

::slack::chat::responses::delete_it chat::delete_wrapper::get_response()
{
    cpr::Parameters params{{"token",   ::slack_config::token_},
                           {"channel", channel_},
                           {"ts",      ts_}
    };

    auto result = cpr::Get(cpr::Url{slack_config::HOSTNAME + "chat.delete"}, params);
    if (result.status_code != 200)
    {
        //error path
        return {result.text}; //TODO
    }
    //happy path
    Json::Value result_ob;
    Json::Reader reader;
    bool parsedSuccess = reader.parse(result.text, result_ob, false);
    if (!parsedSuccess)
    {
        return {result.text}; //TODO
    }

    ::slack::chat::responses::delete_it ret{result.text};

    ret.ok = result_ob["ok"].asBool();

    if (!ret)
    {
        ret.error = result_ob["error"].asString();
    }
    else
    {
        ret.channel = result_ob["channel"].asString();
        ret.ts = result_ob["ts"].asString();
    }

    return ret;
}

::slack::chat::responses::delete_it delete_it(ts ts, channel_id channel)
{
    class delete_wrapper wrapper{ts, channel};
    return wrapper.get_response();
}

::slack::chat::responses::post_message chat::post_message_wrapper::get_response()
{
    cpr::Parameters params{{"token",   ::slack_config::token_},
                           {"channel", channel_},
                           {"text",    text_}
    };

    //optional parameters
    if (ts_)
    {
        params.AddParameter({"ts", *ts_});
    }
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
        if (*parse_ == parse::full)
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
        return {result.text}; //TODO we need a different constructor for error conditions
    }

    return {result.text};

}


::slack::chat::responses::post_message post_message(channel_id channel, text text)
{
    class post_message_wrapper wrapper{channel, text};
    return wrapper.get_response();
}

namespace responses
{

/********* post_message response ***********/

::slack::chat::responses::post_message::post_message(const std::string &raw_json) : raw_json{raw_json}
{
    //happy path
    Json::Value result_ob;
    Json::Reader reader;
    bool parsedSuccess = reader.parse(raw_json, result_ob, false);
    if (!parsedSuccess)
    {
        error = error::unknown; //TODO need more nuance here
        return;
    }

    //TODO need to do more rigorous checking here.
    ok = result_ob["ok"].isBool() ? result_ob["ok"].asBool() : false;

    if (!ok)
    {
        if (!result_ob["error"].isString())
        {
            error = error::unknown; //TOOD more nuance!!
            return;
        }

        auto err_msg = result_ob["error"].asString();

        if (err_msg == "channel_not_found") error = error::channel_not_found;
        else if (err_msg == "not_in_channel") error = error::not_in_channel;
        else if (err_msg == "is_archived") error = error::is_archived;
        else if (err_msg == "msg_too_long") error = error::msg_too_long;
        else if (err_msg == "no_text") error = error::no_text;
        else if (err_msg == "rate_limited") error = error::rate_limited;
        else if (err_msg == "not_authed") error = error::not_authed;
        else if (err_msg == "invalid_auth") error = error::invalid_auth;
        else if (err_msg == "account_inactive") error = error::account_inactive;
    }
    else
    {
        //TODO MORE RIGOROUS CHECKS!
        channel = result_ob["channel"].asString();
        ts = result_ob["ts"].asString();
        message = ::slack::message{result_ob["message"]};
    }

    return;
}
} //namespace responses
} //nanespace chat
} //namespace slack