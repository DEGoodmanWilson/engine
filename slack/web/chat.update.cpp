//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/web/chat.update.h"
#include "private.h"
#include <sstream>

namespace slack { namespace chat
{

const std::string update::error::MESSAGE_NOT_FOUND = std::string{"message_not_found"};
const std::string update::error::CHANNEL_NOT_FOUND = std::string{"channel_not_found"};
const std::string update::error::CANT_DELETE_MESSAGE = std::string{"cant_delete_message"};
const std::string update::error::COMPLIANCE_EXPORTS_PREVENT_DELETION = std::string{
        "compliance_exports_prevent_deletion"};
const std::string update::error::NOT_AUTHED = std::string{"not_authed"};
const std::string update::error::INVALID_AUTH = std::string{"invalid_auth"};
const std::string update::error::ACCOUNT_INACTIVE = std::string{"account_inactive"};

void update::initialize_()
{
    auto params = default_params({
            {"ts",      ts_},
            {"channel", channel_},
            {"text",    text_}
    });

    //optional parameters
    if (parse_)
    {
        std::string parse_val{"none"};
        switch (*parse_)
        {
            case parameter::parse::none:
                parse_val = "none";
                break;
            case parameter::parse::full:
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
        //TODO this is ugly, but we need json strings.
        Json::Value root;
        for (auto &a : *attachments_)
        {
            root.append(a);
        }

        //TODO there is probably a better way?
        std::stringstream ss;
        ss << root;
        params.emplace("attachments", ss.str());
    }

    auto result_ob = slack_private::get(this, "chat.update", params);

    if(this->success())
    {
        if (result_ob["channel"].isString()) channel = slack::channel_id{result_ob["channel"].asString()};
        if (result_ob["ts"].isString()) ts = slack::ts{result_ob["ts"].asString()};
        if (result_ob["text"].isString()) text = result_ob["text"].asString();
    }
}

}} //namespace chat slack