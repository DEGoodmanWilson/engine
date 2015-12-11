//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/config.h"

namespace slack_config
{

std::string token_ = "";

} //namespace slack_config

namespace slack
{

void set_token(std::string token)
{
    ::slack_config::token_ = token;
}


std::string get_token()
{
    return ::slack_config::token_;
}

} //namespace slack