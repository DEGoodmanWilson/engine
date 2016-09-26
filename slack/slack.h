//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <slack/config.h>
#include <slack/types.h>
#include <slack/api.h>
#include <slack/auth.h>
#include <slack/channels.h>
#include <slack/chat.h>
#include <slack/oauth.h>
#include <slack/rtm.h>
#include <slack/users.h>
#include <slack/rtm_event_client.h>
#include <slack/http_event_client.h>
#include <slack/base/slack_delegate.h>

namespace slack
{

class slack : slack_delegate
{
public:
    slack();
    template<class T>
    slack(T &&token);

    static void set_uri(const std::string &uri);
    static std::string get_uri();
    std::string token() const;
    void reset_token(const std::string &token);
    void reset_token(std::string &&token);
    const ::slack::containers::api api;
    const ::slack::containers::auth auth;
    const ::slack::containers::channels channels;
    const ::slack::containers::chat chat;
    const ::slack::containers::oauth oauth;
    const ::slack::containers::users users;
    const ::slack::containers::rtm rtm;
private:
    access_token token_;
    static std::string uri_;
};

} //namespace slack