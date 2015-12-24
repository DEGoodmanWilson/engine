//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/websocket.h"

#include <Simple-WebSocket-Server/client_wss.hpp>

std::unique_ptr<SimpleWeb::SocketClient<SimpleWeb::WSS>> wss_client_;

namespace slack
{

class simple_websocket::simple_websocket_impl :
        public websocket
{

    using WssClient = SimpleWeb::SocketClient<SimpleWeb::WSS>;


public:
    simple_websocket_impl(const std::string &url, simple_websocket *delegate) :
            wss_client_{std::string{url}.erase(0, 6), false}, //TODO MAKE THIS TRUE!
            delegate_{delegate}
    {
        wss_client_.onopen = std::bind(&simple_websocket_impl::on_connect_, this);
        wss_client_.onclose = std::bind(&simple_websocket_impl::on_close_,
                                         this,
                                         std::placeholders::_1,
                                         std::placeholders::_2);
        wss_client_.onerror = std::bind(&simple_websocket_impl::on_error_, this, std::placeholders::_1);
        wss_client_.onmessage = std::bind(&simple_websocket_impl::on_message_, this, std::placeholders::_1);
    }


    virtual void start() override
    {
        wss_client_.start();
    }

    virtual void stop() override
    {
        wss_client_.stop();
    }

    virtual void send_message(const std::string &message) override
    {
        auto send_stream = std::make_shared<WssClient::SendStream>();
        *send_stream << message;
        wss_client_.send(send_stream);
    }


private:
    simple_websocket *delegate_;

    void on_connect_()
    {
        if (delegate_->on_connect)
        {
            delegate_->on_connect();
        }
    }


    void on_close_(int status, const std::string &reason)
    {
        if (delegate_->on_close)
        {
            //TODO
            delegate_->on_close(websocket::close_reason::NETWORK_ERROR);
        }
    }


    void on_error_(const boost::system::error_code &error_code)
    {
        if (delegate_->on_error)
        {
            //TODO
            delegate_->on_error(websocket::error_code::UNKNOWN);
        }
    }


    void on_message_(std::shared_ptr<WssClient::Message> mesg)
    {
        if (delegate_->on_message)
        {
            delegate_->on_message(mesg->string());
        }
    }

    WssClient wss_client_;
};


simple_websocket::simple_websocket(const std::string &url)
        : impl_{new simple_websocket_impl{url, this}}
{ }

simple_websocket::~simple_websocket() = default;

void slack::simple_websocket::start()
{
    impl_->start();
}

void slack::simple_websocket::stop()
{
    impl_->stop();
}

void slack::simple_websocket::send_message(const std::string &message)
{
    impl_->send_message(message);
}

} //namespace slack

