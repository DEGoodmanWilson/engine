//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/http.h"
#include <cpr.h>

namespace slack {

class simple_http::simple_http_impl : public http
{
public:

    virtual response get(const std::string &url, const params &params) override
    {
        cpr::Parameters p;
        for (auto &kv : params)
        {
            p.AddParameter({kv.first, kv.second});
        }

        auto response = cpr::Get(cpr::Url{url}, p);

        return {static_cast<uint32_t>(response.status_code), response.text};
    }

    virtual response post(const std::string &url, const params &params) override
    {
        cpr::Parameters p;
        for (auto &kv : params)
        {
            p.AddParameter({kv.first, kv.second});
        }

        auto response = cpr::Post(cpr::Url{url}, p);

        return {static_cast<uint32_t>(response.status_code), response.text};
    }
};

simple_http::simple_http()
        : impl_{new simple_http_impl}
{ }

simple_http::~simple_http() = default;

http::response simple_http::get(const std::string &url, const http::params &params)
{
    return impl_->get(url, params);
}

http::response simple_http::post(const std::string &url, const http::params &params)
{
    return impl_->post(url, params);
}

} //namespace http slack