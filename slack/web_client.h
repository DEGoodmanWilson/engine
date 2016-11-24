//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <slack/base/slack_delegate.h>
#include <slack/config.h>
#include <slack/types.h>
#include <slack/api.h>
#include <slack/auth.h>
#include <slack/channels.h>
#include <slack/chat.h>
#include <slack/oauth.h>
#include <slack/rtm.h>
#include <slack/users.h>

namespace slack
{

class web_client : slack_delegate
{
public:
    web_client();
    web_client(const std::string &token);
    web_client(std::string &&token);

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