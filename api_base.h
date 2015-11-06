//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
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
    api_base(plaid *delegate);


protected:
    boost::network::http::client::response get_(const std::string &method,
                                                const std::experimental::optional<std::multimap<std::string, std::string>> params = std::experimental::nullopt);

private:
    plaid *delegate_;
};


} //namespace slack