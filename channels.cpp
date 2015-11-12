//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/channels.h"
#include "config.h"
#include <cpr.h>
#include <json/json.h>


namespace slack_config
{
extern std::string token_;
}

namespace slack
{

namespace channels
{

::slack::response::channels::list channels::list_wrapper::get_response()
{
    cpr::Parameters params{{"token",   ::slack_config::token_}};
    if(exclude_archived_)
    {
        params.AddParameter({"exclude_archived", exclude_archived_});
    }

    auto result = cpr::Get(cpr::Url{slack_config::HOSTNAME + "channels.list"}, params);
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

    ::slack::response::channels::list ret{result.text};

    ret.ok = result_ob["ok"].asBool();

    if (!ret)
    {
        ret.error = result_ob["error"].asString();
    }
    else
    {
//append channels to results!
    }

    return ret;
}

}
} //namespace slack