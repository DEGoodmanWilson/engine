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

namespace slack { namespace rtm
{

class start :
        public slack::base::response
{
public:
    //public interface
    template<typename ...Os>
    start(const std::string& token) : response{token}
    {
        initialize_();
    }

    template<typename ...Os>
    start(const std::string& token, Os &&...os) : response{token}
    {
        slack::set_option<start>(*this, std::forward<Os>(os)...);
        initialize_();
    }

    //parameters
    struct parameter
    {
        MAKE_BOOL_LIKE(simple_latest);

        MAKE_BOOL_LIKE(no_unreads);

        MAKE_BOOL_LIKE(mpim_aware);
    };

    //errors
    struct error :
            public slack::base::error
    {
        static const std::string MIGRATION_IN_PROGRESS;
        static const std::string NOT_AUTHED;
        static const std::string INVALID_AUTH;
        static const std::string ACCOUNT_INACTIVE;
    };

    //response
    std::experimental::optional<std::string> url;
//    std::experimental::optional<user> self;
//    std::experimental::optional<team> team;
//    std::experimental::optional<std::vector<user>> users;
//    std::experimental::optional<std::vector<channel>> channels;
//    std::experimental::optional<std::vector<group>> groups;
//    std::experimental::optional<std::vector<mpim>> mpims;
//    std::experimental::optional<std::vector<im>> ims;
//    std::experimental::optional<std::vector<bot>> bots;

    //parameter setters
    void set_option(const parameter::simple_latest &simple_latest)
    { simple_latest_ = simple_latest; }

    void set_option(parameter::simple_latest &&simple_latest)
    { simple_latest_ = std::move(simple_latest); }

    void set_option(const parameter::no_unreads &no_unreads)
    { no_unreads_ = no_unreads; }

    void set_option(parameter::no_unreads &&no_unreads)
    { no_unreads_ = std::move(no_unreads); }

    void set_option(const parameter::mpim_aware &mpim_aware)
    { mpim_aware_ = mpim_aware; }

    void set_option(parameter::mpim_aware &&mpim_aware)
    { mpim_aware_ = std::move(mpim_aware); }

private:
    void initialize_();

    std::experimental::optional<parameter::simple_latest> simple_latest_;
    std::experimental::optional<parameter::no_unreads> no_unreads_;
    std::experimental::optional<parameter::mpim_aware> mpim_aware_;
};

}}  //namespace rtm slack