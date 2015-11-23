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

responses::list channels::list_wrapper::get_response()
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

    responses::list ret{result.text};

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

namespace responses
{
list::list(const std::string &raw_json) : raw_json{raw_json}, ok{false}, error{"responseparse failure"}
{
    Json::Value root;
    Json::Reader reader;
    bool parsedSuccess = reader.parse(raw_json, root, false);
    if (!parsedSuccess) return; //we're done

    ok = root["ok"].asBool();
    if(!ok)
    {
        error = root["error"].asString();
        return; //we're done;
    }

    for(const auto channel_obj : root["channels"])
    {
        channel chan{channel_obj};
        channels.emplace_back(chan);
    }

//    if (!result_ob["args"].isNull() && result_ob["args"].isObject())
//    {
//        std::multimap<std::string, std::string> args;
//        for (const auto arg: result_ob["args"].getMemberNames())
//        {
//            args.emplace(arg, result_ob["args"][arg].asString());
//        }
//    }

}
} //nanespace responses

} //namespace channel
} //namespace slack