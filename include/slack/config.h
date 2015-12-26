//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/http.h>
#include <string>

namespace slack
{

void set_token(std::string token);

std::string get_token();

void set_http(std::shared_ptr<http> http);
std::shared_ptr<http> get_http();

}

