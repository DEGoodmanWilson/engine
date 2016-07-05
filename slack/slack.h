//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <slack/types.h>
#include <slack/api.h>
#include <slack/chat.h>
#include <slack/base/slack_delegate.h>

namespace slack
{

class slack : slack_delegate
{
public:
    slack(const std::string &token);
    slack(std::string &&token);

    std::string token() const;
    const ::slack::containers::api api;
    const ::slack::containers::chat chat;
private:
    const std::string token_;
};

} //namespace slack