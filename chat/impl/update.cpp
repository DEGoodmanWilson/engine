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

//TODO 1st priority almost all of these looks exactly alike. How can we consolidate this code? A template, clearly!
response::update update::get_response()
{
    cpr::Parameters params{
            {"token",   slack_config::token_},
            {"ts", ts_},
            {"channel", channel_},
            {"test",    text_}
    };

    //optional parameters
    if (parse_)
    {
        std::string parse_val{"none"};
        if (*parse_ == parameter::update::parse::full)
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

    auto result = cpr::Get(cpr::Url{slack_config::HOSTNAME + "chat.update"}, params);
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
