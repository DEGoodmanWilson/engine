//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/http.h"
#include <cpr.h>

namespace slack { namespace http
{

std::function<response(std::string url, params)> get = [](std::string url,
                                                          slack::http::params params) -> slack::http::response {
    cpr::Parameters p;
    for (auto &kv : params)
    {
        p.AddParameter({kv.first, kv.second});
    }

    auto response = cpr::Get(cpr::Url{url}, p);

    return {static_cast<uint32_t>(response.status_code), response.text};
};

std::function<response(std::string url, params)> post = [](std::string url,
                                                           slack::http::params params) -> slack::http::response {
    cpr::Parameters p;
    for (auto &kv : params)
    {
        p.AddParameter({kv.first, kv.second});
    }

    auto response = cpr::Post(cpr::Url{url}, p);

    return {static_cast<uint32_t>(response.status_code), response.text};
};

}} //namespace http slack
