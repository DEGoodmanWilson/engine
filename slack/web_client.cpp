//
// Created by Donald Goodman-Wilson on 7/3/16.
//

#include "web_client.h"

namespace slack
{


std::string web_client::uri_ = "https://slack.com/api/";

web_client::web_client() : token_{""},
                 api{this},
                 auth{this},
                 channels{this},
                 chat{this},
                 oauth{this},
                 users{this},
                 rtm{this}
{}

web_client::web_client(const std::string &token) : token_{token},
                                         api{this},
                                         auth{this},
                                         channels{this},
                                         chat{this},
                                         oauth{this},
                                         users{this},
                                         rtm{this}
{}

web_client::web_client(std::string &&token) : token_{std::move(token)},
                                    api{this},
                                    auth{this},
                                    channels{this},
                                    chat{this},
                                    oauth{this},
                                    users{this},
                                    rtm{this}
{}

void web_client::set_uri(const std::string &uri)
{
    uri_ = uri;
}

std::string web_client::get_uri()
{
    return uri_;
}

std::string web_client::token() const
{
    return token_;
}

void web_client::reset_token(const std::string &token)
{
    token_ = token;
}

void web_client::reset_token(std::string &&token)
{
    token_ = std::move(token);
}

} //namespace