//
// Created by Donald Goodman-Wilson on 7/3/16.
//

#include "slack.h"

namespace slack
{


std::string slack::uri_ = "https://slack.com/api/";

slack::slack() : token_{""},
                 api{this},
                 auth{this},
                 channels{this},
                 chat{this},
                 oauth{this},
                 users{this},
                 rtm{this}
{}

slack::slack(const std::string &token) : token_{token},
                                         api{this},
                                         auth{this},
                                         channels{this},
                                         chat{this},
                                         oauth{this},
                                         users{this},
                                         rtm{this}
{}

slack::slack(std::string &&token) : token_{std::move(token)},
                                    api{this},
                                    auth{this},
                                    channels{this},
                                    chat{this},
                                    oauth{this},
                                    users{this},
                                    rtm{this}
{}

slack::slack(const access_token &token) : token_{token},
                                          api{this},
                                          auth{this},
                                          channels{this},
                                          chat{this},
                                          oauth{this},
                                          users{this},
                                          rtm{this}
{}

slack::slack(access_token &&token) : token_{std::move(token)},
                                     api{this},
                                     auth{this},
                                     channels{this},
                                     chat{this},
                                     oauth{this},
                                     users{this},
                                     rtm{this}
{}

void slack::set_uri(const std::string &uri)
{
    uri_ = uri;
}

std::string slack::get_uri()
{
    return uri_;
}

std::string slack::token() const
{
    return token_;
}

void slack::reset_token(const std::string &token)
{
    token_ = token;
}

void slack::reset_token(std::string &&token)
{
    token_ = std::move(token);
}

} //namespace