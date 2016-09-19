//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <vector>
#include <string>
#include <slack/optional.hpp>

namespace slack { namespace users
{

class list :
        public slack::base::response
{
public:
    //public interface
//    list(const list &other) = default;
//    list(list &&other) = default;
//    list(list &other)
//            : list(const_cast<const list &>(other))
//    { }

    template<class TOKEN, typename ...Os>
    list(TOKEN &&token) :
            response{std::forward<TOKEN>(token)}
    {
        initialize_();
    }

    template<class TOKEN, typename ...Os>
    list(TOKEN &&token, Os &&...os) :
            response{std::forward<TOKEN>(token)}
    {
        slack::set_option<list>(*this, std::forward<Os>(os)...);
        initialize_();
    }

    //parameters
    struct parameter
    {
        SLACK_MAKE_BOOL_LIKE(presence);
    };

    //errors
    struct error :
            public slack::base::error
    {
        static const std::string NOT_AUTHED;
        static const std::string INVALID_AUTH;
        static const std::string ACCOUNT_INACTIVE;
    };

    //response
    std::vector<user> members;

    //parameter setters
    void set_option(const parameter::presence &presence)
    { presence_ = presence; }

    void set_option(parameter::presence &&presence)
    { presence_ = std::move(presence); }

private:
    void initialize_();

    std::experimental::optional<parameter::presence> presence_;
};

}} //namespace users slack