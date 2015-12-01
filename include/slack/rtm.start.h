//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <slack/base/impl.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>

namespace slack
{
namespace rtm
{

/*************************************************************/
// MARK: - Parameters

namespace parameter
{
namespace start
{

MAKE_BOOL_LIKE(simple_latest);

MAKE_BOOL_LIKE(no_unreads);

MAKE_BOOL_LIKE(mpim_aware);

} //namespace start
} //namespace parameter

/*************************************************************/
// MARK: - Response Errors

namespace response
{
namespace error
{
namespace start
{

const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
const auto MIGRATION_IN_PROGRESS = std::string{"migration_in_progress"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};

} //namespace start
} //namespace error
} //namespace response


/*************************************************************/
// MARK: - Response

namespace response
{

struct start :
        public slack::base::response
{
    start(const std::string &raw_json);

    std::experimental::optional<std::string> url;
//    std::experimental::optional<user> self;
//    std::experimental::optional<team> team;
//    std::experimental::optional<std::vector<user>> users;
    std::experimental::optional<std::vector<channel>> channels;
//    std::experimental::optional<std::vector<group>> groups;
//    std::experimental::optional<std::vector<mpim>> mpims;
//    std::experimental::optional<std::vector<im>> ims;
//    std::experimental::optional<std::vector<bot>> bots;
};

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

class start :
        public slack::base::impl<response::start>
{
public:
    start() = default;

    //TODO can these be moved into the base class?
    response::start get_response();

    void set_option(const parameter::start::simple_latest &simple_latest)
    { simple_latest_ = simple_latest; }

    void set_option(parameter::start::simple_latest &&simple_latest)
    { simple_latest_ = std::move(simple_latest); }

    void set_option(const parameter::start::no_unreads &no_unreads)
    { no_unreads_ = no_unreads; }

    void set_option(parameter::start::no_unreads &&no_unreads)
    { no_unreads_ = std::move(no_unreads); }

    void set_option(const parameter::start::mpim_aware &mpim_aware)
    { mpim_aware_ = mpim_aware; }

    void set_option(parameter::start::mpim_aware &&mpim_aware)
    { mpim_aware_ = std::move(mpim_aware); }

private:
    std::experimental::optional<parameter::start::simple_latest> simple_latest_;
    std::experimental::optional<parameter::start::no_unreads> no_unreads_;
    std::experimental::optional<parameter::start::mpim_aware> mpim_aware_;
};

} //namespace impl


/*************************************************************/
// MARK: - Public Interface


template<typename ...Os>
response::start start()
{
    class impl::start impl;
    return impl.get_response();
}

template<typename ...Os>
response::start start(Os &&...os)
{
    class impl::start impl;

    set_option<decltype(impl)>(impl, std::forward<Os>(os)
            ...);
    return impl.

            get_response();
}

} //namespace rtm
} //namespace slack