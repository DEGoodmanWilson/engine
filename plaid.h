//
// Created by D.E. Goodman-Wilson on 11/5/15.
//

#pragma once

#include <boost/network/protocol/http/client.hpp>
#include <optional/optional.hpp>
#include <string>
#include <map>

namespace slack
{

class plaid;

class api_base
{
public:
    api_base(plaid *delegate) :
            delegate_(delegate)
    { }

protected:
    plaid *delegate_;
};


class plaid
{
    class auth :
            api_base
    {
    public:
        auth(plaid *delegate) : api_base(delegate)
        { }

        std::string test();
    };

public:
    plaid(std::string token);

    auth auth;
private:
    std::string token_;
    boost::network::http::client client_;

    boost::network::http::client::response get_(const std::string &method,
                                                const std::experimental::optional<std::multimap<std::string, std::string>> params = std::experimental::nullopt);
};

} //namespace slack