//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/event/message.h>

namespace slack
{

struct channel
{
    channel() = default;

    template<class json>
    channel(const json &parsed_json);

    struct topic
    {
        std::string value;
        user_id creator;
        int64_t last_set;
    };

    struct purpose
    {
        std::string value;
        user_id creator;
        int64_t last_set;
    };

    channel_id id;
    std::string name;
    bool is_channel;
    int64_t created;
    user_id creator;
    bool is_archived;
    bool is_general;
    std::vector<user_id> members;
    topic topic;
    purpose purpose;
    bool is_member;
    ts last_read;
    event::message latest;
    int64_t unread_count;
    int64_t unread_display_count;
};

} //namespace slack