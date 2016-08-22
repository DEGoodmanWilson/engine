//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>

namespace slack { namespace oauth
{

class access :
        public slack::base::response
{
public:
    //public interface

    template<class TOKEN, class CLIENT_ID, class CLIENT_SECRET, class CODE, typename ...Os>
    access(TOKEN &&token,
           CLIENT_ID &&client_id,
           CLIENT_SECRET &&client_secret,
           CODE &&code) :
            response{std::forward<TOKEN>(token)},
            client_id_{std::forward<CLIENT_ID>(client_id)},
            client_secret_{std::forward<CLIENT_SECRET>(client_secret)},
            code_{std::forward<CODE>(code)}
    {
        initialize_();
    }

    template<class TOKEN, class CLIENT_ID, class CLIENT_SECRET, class CODE, typename ...Os>

    access(TOKEN &&token,
           CLIENT_ID &&client_id,
           CLIENT_SECRET &&client_secret,
           CODE &&code,
           Os &&...os) :
            response{std::forward<TOKEN>(token)},
            client_id_{std::forward<CLIENT_ID>(client_id)},
            client_secret_{std::forward<CLIENT_SECRET>(client_secret)},
            code_{std::forward<CODE>(code)}
    {
        slack::set_option<access>(*this, std::forward<Os>(os)...);
        initialize_();
    }

    //parameters
    struct parameter
    {
        MAKE_STRING_LIKE(redirect_uri);
    };

    //errors
    struct error :
            public slack::base::error
    {
        static const std::string INVALID_CLIENT_ID;
        static const std::string BAD_CLIENT_SECRET;
        static const std::string INVALID_CODE;
        static const std::string BAD_REDIRECT_URI;
    };

    //response
    struct bot
    {
        slack::user_id bot_user_id;
        slack::token bot_access_token;
    };

    slack::token access_token;
    std::vector<slack::scope> scope;
    slack::user_id user_id;
    std::string team_name;
    slack::team_id team_id;
    std::experimental::optional<struct bot> bot;

    //parameter setters
    void set_option(const parameter::redirect_uri &redirect_uri)
    { redirect_uri_ = redirect_uri; }

    void set_option(parameter::redirect_uri &&redirect_uri)
    { redirect_uri_ = std::move(redirect_uri); }

private:
    void initialize_();

    std::string client_id_;
    std::string client_secret_;
    std::string code_;
    std::experimental::optional<parameter::redirect_uri> redirect_uri_;
};

}} //namespace oauth slack