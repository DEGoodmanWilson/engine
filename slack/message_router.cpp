//
// Created by D.E. Goodman-Wilson on 8/19/16.
//

#include "message_router.h"

namespace slack
{

void message_router::message::reply(std::string text) const
{
    slack::slack c{token};
    c.chat.postMessage(channel.id, text);
}


bool message_router::route(const event::message &message)
{
    //TODO I am not super happy with this, and I don't really have a good clue how to improve it.
    for (const auto &handler_pair : callbacks_)
    {
        std::smatch pieces_match;
        auto message_regex = std::get<std::regex>(handler_pair);

        auto callback = std::get<hears_cb>(handler_pair);
        if (std::regex_search(message.text, pieces_match, message_regex))
        {
            //we found it, let's construct a proper message_reply object
            user user;
            if (user_lookup_)
            {
                user = user_lookup_(message.user);
            }
            else
            {
                user.id = message.user;
            }

            channel channel;
            if (channel_lookup_)
            {
                channel = channel_lookup_(message.channel);
            }
            else
            {
                channel.id = message.channel;
            }

            struct message mesg{message.text, user, channel, token_lookup_(message.team_id), message.team_id};

            callback(mesg); //TODO or we could return the retval from the callback, have it return true if handled and false if it chose not to
            return true;
        }
    }

    return false;
}

} //namespace slack