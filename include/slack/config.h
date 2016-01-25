//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/http.h>
#include <string>

namespace slack
{

void set_token(const std::string& token);
std::string get_token();

void set_host(const std::string& host);
std::string get_host();

void set_http(std::shared_ptr<http> http);
std::shared_ptr<http> get_http();

}

