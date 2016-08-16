//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <slack/types.h>
#include <slack/api.h>
#include <slack/auth.h>
#include <slack/channels.h>
#include <slack/chat.h>
#include <slack/oauth.h>
#include <slack/rtm.h>
#include <slack/rtm_event_client.h>
#include <slack/http_event_client.h>
#include <slack/base/slack_delegate.h>

namespace slack
{

class slack : slack_delegate
{
public:
    slack();
    slack(const std::string &token);
    slack(std::string &&token);

    std::string token() const;
    void reset_token(const std::string &token);
    void reset_token(std::string &&token);
    const ::slack::containers::api api;
    const ::slack::containers::auth auth;
    const ::slack::containers::channels channels;
    const ::slack::containers::chat chat;
    const ::slack::containers::oauth oauth;
    const ::slack::containers::rtm rtm;
private:
    std::string token_;
};

} //namespace slack