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

::slack::response::chat::delete_it chat::delete_wrapper::get_response()
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

    ::slack::response::chat::delete_it ret{result.text};

    ret.ok = result_ob["ok"].asBool();

    if (!ret)
    {
        ret.error = result_ob["error"].asString();
    }
    else
    {
        ret.channel = result_ob["channel"].asString();
        ret.ts = result_ob["it"].asString();
    }

    return ret;
}

}
} //namespace slack