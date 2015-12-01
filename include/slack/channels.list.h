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
namespace channels
{

/*************************************************************/
// MARK: - Parameters

namespace parameter
{
namespace list
{

MAKE_BOOL_LIKE(exclude_archived);

} //namespace list
} //namespace parameter

/*************************************************************/
// MARK: - Response Errors

namespace response
{
namespace error
{
namespace list
{

const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};

} //namespace list
} //namespace error
} //namespace response


/*************************************************************/
// MARK: - Response

namespace response
{

struct list :
        public slack::base::response
{
    list(const std::string &raw_json);

    std::experimental::optional<std::vector<::slack::channel>> channels;
};

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

class list :
        public slack::base::impl<response::list>
{
public:
    //TODO can these be moved into the base class?
    response::list get_response();

    void set_option(const parameter::list::exclude_archived &exclude_archived)
    { exclude_archived_ = exclude_archived; }

    void set_option(parameter::list::exclude_archived &&exclude_archived)
    { exclude_archived_ = exclude_archived; }

private:
    std::experimental::optional<parameter::list::exclude_archived> exclude_archived_;
};

} //namespace impl


/*************************************************************/
// MARK: - Public Interface


template<typename ...Os>
response::list list()
{
    class impl::list impl;
    return impl.get_response();
}

template<typename ...Os>
response::list list(Os &&...os)
{
    class impl::list impl;
    set_option<decltype(impl)>(impl, std::forward<Os>(os)...);
    return impl.get_response();
}


} //namespace channel
} //namespace slack