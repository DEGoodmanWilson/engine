//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/web/users.list.h"
#include "private.h"
#include <json/json.h>

namespace slack { namespace users
{

void list::initialize_()
{
    auto params = default_params({});

    if (presence_)
    {
        params.emplace("presence", (*presence_) ? "true" : "false");
    }

    auto result_ob = slack_private::get(this, "users.list", params);

    if (!result_ob["members"].isNull() && result_ob["members"].isArray())
    {
        members = std::vector<user>{};

        for (auto member: result_ob["members"])
        {
            members.emplace_back(member);
        }
    }
}

}} //namespace users slack