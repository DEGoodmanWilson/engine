//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>

namespace slack { namespace channels
{

class rename :
        public slack::base::response
{
public:
    //public interface
    template<class TOKEN, class CHANNEL, class NAME>
    rename(TOKEN &&token, CHANNEL &&channel, NAME &&name) :
            response{std::forward<TOKEN>(token)},
            channel_{std::forward<CHANNEL>(channel)},
            name_{std::forward<NAME>(name)}
    {
        initialize_();
    }

    //parameters
    struct parameter
    {
        SLACK_MAKE_BOOL_LIKE(exclude_archived);
    };

    //errors
    struct error :
            public slack::base::error
    {
        static const std::string CHANNEL_NOT_FOUND;
        static const std::string NOT_IN_CHANNEL;
        static const std::string NOT_AUTHORIZED;
        static const std::string INVALID_NAME;
        static const std::string NAME_TAKEN;
        static const std::string NOT_AUTHED;
        static const std::string INVALID_AUTH;
        static const std::string ACCOUNT_INACTIVE;
        static const std::string USER_IS_BOT;
        static const std::string USER_IS_RESTRICTED;
    };

    //response
    std::experimental::optional<slack::channel> channel;

    //parameter setters

private:
    void initialize_();

    channel_id channel_;
    std::string name_;
};

}} //namespace channels slack