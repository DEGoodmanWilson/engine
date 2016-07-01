//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <string>
#include <map>
#include <functional>
#include <memory>

namespace slack
{

class websocket
{
public:
//Functions to invoke callbacks in engine, to be implemented in engine

    std::function<void(void)> on_connect;
    std::function<void(const std::string &)> on_message;
    enum class error_code
    {
        UNKNOWN,
        NETWORK_ERROR,
    };
    std::function<void(error_code)> on_error;
    enum class close_reason
    {
        UNKNOWN,
        CLOSED_BY_CLIENT,
        CLOSED_BY_SERVER,
    };
    std::function<void(close_reason)> on_close;

//Functions engine will call, to be implemented by the client
    virtual void start(const std::string& url) = 0;
    virtual void stop() = 0;
    virtual void send_message(const std::string &message) = 0;
};

//TODO if def this!
// This is a wrapper class around Simple-Websocket-Server that clients can use if they like
class simple_websocket : public websocket
{

public:
    simple_websocket();

    virtual ~simple_websocket();

    virtual void start(const std::string& url) override;

    virtual void stop() override;

    virtual void send_message(const std::string &message) override;

private:
    class simple_websocket_impl;
    std::unique_ptr<simple_websocket_impl> impl_;
};

} //namespace slack