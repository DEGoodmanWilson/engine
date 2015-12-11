//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/base/response.h"
#include "private.h"
#include <json/json.h>

namespace slack
{
namespace base
{

const std::string error::UNKNOWN = "unknown";
const std::string error::JSON_PARSE_FAILURE = "json_parse_failure";
const std::string error::INVALID_RESPONSE = "invalid_response";

} //namespace base
} //namespace slack
