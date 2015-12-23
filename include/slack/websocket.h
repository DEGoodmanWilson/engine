//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <string>
#include <map>
#include <functional>

namespace slack
{

class websocket
{
public:
//Functions to invoke callbacks in engine, to be implemented in engine
    std::function<void(void)> on_open;
    std::function<void(const std::string &)> on_message;
    enum class error_code
    {
        UNKNOWN,
    };
    std::function<void(error_code)> on_error;
    enum class close_reason
    {
        NETWORK_ERROR,
        CLOSED_BY_CLIENT,
        CLOSED_BY_SERVER,
    };
    std::function<void(close_reason)> on_close;

//Functions engine will call, to be implemented by the client
    virtual void open(const std::string &url) = 0;
    virtual void close() = 0;
    virtual void send_message(const std::string &message) = 0;
};

} //namespace slack