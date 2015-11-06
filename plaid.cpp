//
// Created by D.E. Goodman-Wilson on 11/5/15.
//

#include "plaid.h"


namespace slack
{

std::string make_query_string_(const std::experimental::optional<std::multimap<std::string, std::string>> params)
{
    if(!params || params->empty())
    {
        return "";
    }

    auto concat = [](auto const &a) {
        if (a.second.empty())
        {
            return a.first;
        }

        return a.first + "=" + a.second;
    };


    std::string query_string;
    for (auto const &value: *params)
    {
        query_string += "&" + concat(value);
    }

    return query_string;
}

plaid::plaid(std::string token) :
        token_{token},
        auth{this}
{ }


boost::network::http::client::response plaid::get_(const std::string &method,
                                                   const std::experimental::optional<std::multimap<std::string, std::string>> params)
{
    auto query_string = make_query_string_(params);
    boost::network::http::client::request request_(
            "https://slack.com/api/" + method + "?token=" + token_ + query_string);
    request_ << boost::network::header("Connection", "close");
    return client_.get(request_);
}



} //namespace slack