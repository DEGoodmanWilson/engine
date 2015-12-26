//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <string>
#include <map>
#include <functional>

namespace slack
{
class http
{
public:
    using params = std::map<std::string, std::string>;

    struct response
    {
        uint32_t status_code;
        //TODO other error codes here.
        std::string body;
    };

    virtual response get(const std::string& url, const params& params) = 0;

    virtual response post(const std::string& url, const params& params) = 0;
    //put, delete, patch
};

class simple_http : public http
{
public:
    simple_http();
    ~simple_http();

    response get(const std::string &url, const params &params) override;
    response post(const std::string &url, const params &params) override;

private:
    class simple_http_impl;
    std::unique_ptr<simple_http_impl> impl_;
};

} //namespace slack