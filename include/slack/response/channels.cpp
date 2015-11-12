//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/response/channels.h"
#include <json/json.h>

namespace slack
{
namespace response
{
namespace channels
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

}
}
}