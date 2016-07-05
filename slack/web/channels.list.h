//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/channel.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>

namespace slack { namespace channels
{

class list : public slack::base::response
{
public:
    //public interface
    template<typename ...Os>
    list(const std::string& token) : response{token}
    {
        initialize_();
    }

    template<typename ...Os>
    list(const std::string& token, Os &&...os) : response{token}
    {
        slack::set_option<list>(*this, std::forward<Os>(os)...);
        initialize_();
    }

    //parameters
    struct parameter
    {
        MAKE_BOOL_LIKE(exclude_archived);
    };

    //errors
    struct error : slack::base::error
    {
        static const std::string NOT_AUTHED;
        static const std::string INVALID_AUTH;
        static const std::string ACCOUNT_INACTIVE;
    };

    //response
    std::experimental::optional<std::vector<channel>> channels;

    //parameter setters
    void set_option(const parameter::exclude_archived &exclude_archived)
    { exclude_archived_ = exclude_archived; }

    void set_option(parameter::exclude_archived &&exclude_archived)
    { exclude_archived_ = exclude_archived; }


private:
    void initialize_();

    std::experimental::optional<parameter::exclude_archived> exclude_archived_;
};

}} //namespace channels slack