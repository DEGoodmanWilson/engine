//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/config.h"

namespace slack_config
{

std::string token_ = "";

std::shared_ptr<slack::http> http_;

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


void set_http(std::shared_ptr<slack::http> http)
{
    slack_config::http_ = http;
}

std::shared_ptr<slack::http> get_http()
{
    return slack_config::http_;
}


} //namespace slack