//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
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

    template<typename ...Os>
    access(const std::string &client_id, const std::string &client_secret, const std::string &code)
            : client_id_{client_id}, client_secret_{client_secret}, code_{code}
    {
        initialize_();
    }

    template<typename ...Os>
    access(const std::string &client_id, const std::string &client_secret, const std::string &code, Os &&...os)
            : client_id_{client_id}, client_secret_{client_secret}, code_{code}
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
    std::experimental::optional<token> access_token;
    std::experimental::optional<std::vector<scope>> scopes;
    std::experimental::optional<std::string> team_name;
    std::experimental::optional<team_id> team_id;

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