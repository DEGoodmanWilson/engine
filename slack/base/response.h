//
// engine
//
// Copyright © 2015–2017 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/optional.hpp>
#include <slack/http.h>
#include <string>
#include <map>
#include <memory>

namespace slack_private
{
struct json_impl;
}

namespace slack
{
namespace base
{

struct error
{
    static const std::string UNKNOWN;
    static const std::string JSON_PARSE_FAILURE;
    static const std::string INVALID_RESPONSE;
    static const std::string NOT_AUTHED;
    static const std::string INVALID_AUTH;
    static const std::string ACCOUNT_INACTIVE;
};

struct response
{
    response()
    { };

    response(const std::string &token) : token_{token}
    { }

    response(std::string &&token) : token_{std::move(token)}
    { }

    std::string raw_json;
    std::string error_message;

    bool success()
    {
        return error_message.empty(); //if error contains a value, return false
    }

    operator bool()
    {
        return success();
    }

    http::params default_params(http::params params) //TODO yes, we are making a copy. Let's optimize this later
    {
        params.emplace("token", token_);
        return params;
    }

protected:
    std::string token_;
};


} //namespace base
} //namespace slack