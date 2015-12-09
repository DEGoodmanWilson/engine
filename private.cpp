//
// Created by D.E. Goodman-Wilson on 12/8/15.
//

#include "private.h"

namespace slack_private
{

const std::string HOSTNAME = "https://slack.com/api/";


Json::Value get(slack::base::response * obj, std::string endpoint, slack::http::params params, bool auth)
{
    Json::Value result_ob;

    if(auth)
    {
        params["token"] = ::slack::get_token();
    }
    auto response = slack::http::get(HOSTNAME+endpoint, params);
    if(response.status_code != 200)
    {
        //TODO do something!
        obj->error_message = std::string{"TODO"};
        return result_ob;
    }

    Json::Reader reader;
    bool parsed_success = reader.parse(response.body, result_ob, false);
    if (!parsed_success)
    {
        obj->error_message = std::string{"json_parse_failure"};
        return result_ob;
    }

    if (!result_ob["ok"].isBool())
    {
        obj->error_message = std::string{"invalid_response"};
        return result_ob;
    }

    auto ok = result_ob["ok"].asBool();

    if (!ok)
    {
        obj->error_message = result_ob["error"].asString();
        return result_ob;
    }

    return result_ob;
}

} //namespace slack_private