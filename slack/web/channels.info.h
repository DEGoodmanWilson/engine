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

class info :
        public slack::base::response
{
public:
    //public interface
    template<class TOKEN, class CHANNEL>
    info(TOKEN &&token, CHANNEL &&channel) :
            response{std::forward<TOKEN>(token)},
            channel_{std::forward<CHANNEL>(channel)}
    {
        initialize_();
    }

    //parameters
    struct parameter
    {
    };

    //errors
    struct error :
            public slack::base::error
    {
        static const std::string CHANNEL_NOT_FOUND;
        static const std::string NOT_AUTHED;
        static const std::string INVALID_AUTH;
        static const std::string ACCOUNT_INACTIVE;
    };

    //response
    slack::channel channel;

private:
    void initialize_();

    channel_id channel_;
};

}} //namespace channels slack