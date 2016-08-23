//
// Created by D.E. Goodman-Wilson on 12/8/15.
//

#include "private.h"
#include "slack.h"
#include <cpr/cpr.h>

namespace slack_private
{


Json::Value parse(slack::base::response *obj, const std::string &json)
{
    obj->raw_json = json;

    Json::Value result_ob;

    Json::Reader reader;
    bool parsed_success = reader.parse(json, result_ob, false);
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

Json::Value get(slack::base::response *obj, const std::string &endpoint, const slack::http::params &params, bool auth)
{
    Json::Value result_ob;

    cpr::Parameters p;
    for (auto &kv : params)
    {
        p.AddParameter({kv.first, kv.second});
    }

    auto response = cpr::Get(cpr::Url{slack::slack::get_uri() + endpoint}, p);

    if (response.status_code != 200)
    {
        //TODO do something!
        obj->error_message = std::string{"TODO"};
        return result_ob;
    }

    return parse(obj, response.text);
}

// TODO should this be static instead of a singleton?
factory<slack::base::event> events_factory;

} //namespace slack_private