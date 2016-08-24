//
// Created by D.E. Goodman-Wilson on 8/19/16.
//

#pragma once

#include <slack/slack.h>
#include <slack/types.h>
#include <slack/event/message.h>
#include <regex>
#include <vector>
#include <utility>

namespace slack
{

class message_router
{
public:

    struct message
    {
        std::string text;
        user from;
        channel channel;

        void reply(std::string text) const;

        std::string token;
        struct team_id team_id;
    };

    using token_lookup_delegate = std::function<std::string(const std::string &)>;
    using user_lookup_delegate = std::function<user(const user_id &)>;
    using channel_lookup_delegate = std::function<channel(const channel_id &)>;

    message_router(token_lookup_delegate delegate) : token_lookup_{delegate}
    {}

    template<typename ...Os>
    message_router(token_lookup_delegate delegate, Os &&...os) : token_lookup_{delegate}
    {
        set_options_(SLACK_FWD(os)...);
    }

    ~message_router() = default;

    bool route(const event::message &message);

    //TODO we want to eventually move to message, really.
    //TODO we want to be able to limit matches against mentions and direct mentions as well! Which means we need to know our user_id!
    using hears_cb = std::function<void(const struct message &message)>;

    template<typename T>
    void hears(T &&message, hears_cb callback)
    {
        callbacks_.emplace_back(std::regex{std::forward<T>(message)}, callback);
    }

private:
    template<typename T>
    void set_options_(T &&t)
    {
        set_option_(SLACK_FWD(t));
    }

    template<typename T, typename... Ts>
    void set_options_(T &&t, Ts &&... ts)
    {
        set_options_(SLACK_FWD(t));
        set_options_(SLACK_FWD(ts)...);
    }

    void set_option_(user_lookup_delegate delegate)
    {
        user_lookup_ = delegate;
    }

    void set_option_(channel_lookup_delegate delegate)
    {
        channel_lookup_ = delegate;
    }

    //let's just brute force this for now
    std::vector<std::pair<std::regex, hears_cb>> callbacks_;

    token_lookup_delegate token_lookup_;
    user_lookup_delegate user_lookup_;
    channel_lookup_delegate channel_lookup_;
};

} //namespace slack