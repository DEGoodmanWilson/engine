//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "api_base.h"
#include "plaid.h"

namespace slack
{

api_base::api_base(plaid *delegate) :
        delegate_(delegate)
{ }


boost::network::http::client::response api_base::get_(const std::string &method,
                                                      const std::experimental::optional<std::multimap<std::string, std::string>> params)
{
    return delegate_->get_(method, params);
}
} //namespace slack