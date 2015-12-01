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
namespace oauth
{

/*************************************************************/
// MARK: - Parameters

namespace parameter
{
namespace access
{

MAKE_STRING_LIKE(redirect_uri);

} //namespace access
} //namespace parameter

/*************************************************************/
// MARK: - Response Errors

namespace response
{
namespace error
{
namespace access
{

const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
const auto INVALID_CLIENT_ID = std::string{"invalid_client_id"};
const auto BAD_CLIENT_SECRET = std::string{"bad_client_secret"};
const auto INVALID_CODE = std::string{"invalid_code"};
const auto BAD_REDIRECT_URI = std::string{"bad_redirect_uri"};

} //namespace access
} //namespace error
} //namespace response


/*************************************************************/
// MARK: - Response

namespace response
{

struct access :
        public slack::base::response
{
    access(const std::string &raw_json);

    std::experimental::optional<token> access_token;
//    std::experimental::optional<std::vector<scope>> scope; //this should be how it is handled. Until I can discover otherwise
    std::experimental::optional<scope> scope;

};

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

class access :
        public slack::base::impl<response::access>
{
public:
    access(const std::string& client_id, const std::string& client_secret, const std::string& code);
    //TODO can these be moved into the base class?
    response::access get_response();

    void set_option(const parameter::access::redirect_uri &redirect_uri)
    { redirect_uri_ = redirect_uri; }

    void set_option(parameter::access::redirect_uri &&redirect_uri)
    { redirect_uri_ = std::move(redirect_uri); }

private:
    std::string client_id_;
    std::string client_secret_;
    std::string code_;
    std::experimental::optional<parameter::access::redirect_uri> redirect_uri_;
};

} //namespace impl


/*************************************************************/
// MARK: - Public Interface


template<typename ...Os>
response::access access(const std::string& client_id, const std::string& client_secret, const std::string& code)
{
    class impl::access impl{client_id, client_secret, code};
    return impl.get_response();
}

template<typename ...Os>
response::access access(const std::string& client_id, const std::string& client_secret, const std::string& code, Os &&...os)
{
    class impl::access impl{client_id, client_secret, code};
    set_option<decltype(impl)>(impl, std::forward<Os>(os)...);
    return impl.get_response();
}


} //namespace oauth
} //namespace slack