//
// Created by Donald Goodman-Wilson on 7/3/16.
//

#include "slack.h"

namespace slack
{

slack::slack(const std::string &token) : token_{token},
                                         api{this},
                                         auth{this},
                                         channels{this},
                                         chat{this},
                                         oauth{this},
                                         rtm{this}
{ }

slack::slack(std::string &&token) : token_{std::move(token)},
                                    api{this},
                                    auth{this},
                                    channels{this},
                                    chat{this},
                                    oauth{this},
                                    rtm{this}
{ }

std::string slack::token() const
{
    return token_;
}

void slack::reset_token(const std::string& token)
{
    token_ = token;
}

void slack::reset_token(std::string&& token)
{
    token_ = std::move(token);
}

} //namespace