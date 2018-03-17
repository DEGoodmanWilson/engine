//
// engine
//
// Copyright © 2017 D.E. Goodman-Wilson. All rights reserved.
//

#include "response.h"

namespace slack { namespace base
{

const std::string error::UNKNOWN = std::string{"unknown"};
const std::string error::JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const std::string error::INVALID_RESPONSE = std::string{"invalid_response"};
const std::string error::NOT_AUTHED = std::string{"not_authed"};
const std::string error::INVALID_AUTH = std::string{"invalid_auth"};
const std::string error::ACCOUNT_INACTIVE = std::string{"account_inactive"};

}} //namespace base slack