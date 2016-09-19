//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>

namespace slack { namespace users
{

class info :
        public slack::base::response
{
public:
    //public interface
    template<class TOKEN, class USER_ID>
    info(TOKEN &&token, USER_ID &&user) :
            response{std::forward<TOKEN>(token)}, user_{std::forward<USER_ID>(user)}
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
        static const std::string USER_NOT_FOUND;
        static const std::string USER_NOT_VISIBLE;
        static const std::string NOT_AUTHED;
        static const std::string INVALID_AUTH;
        static const std::string ACCOUNT_INACTIVE;
    };

    //response
    slack::user user;

    //parameter setters

private:
    void initialize_();

    user_id user_;
};

}} //namespace users slack