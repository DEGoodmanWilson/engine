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
    simple_websocket_impl(simple_websocket *delegate) : delegate_(delegate)
    { }


    virtual void open(const std::string &url) override
    {
        wss_client_ = std::make_unique<WssClient>(std::string{url}.erase(0, 6));
        wss_client_->onopen = std::bind(&simple_websocket_impl::on_open_, this);
        wss_client_->onclose = std::bind(&simple_websocket_impl::on_close_,
                                         this,
                                         std::placeholders::_1,
                                         std::placeholders::_2);
        wss_client_->onerror = std::bind(&simple_websocket_impl::on_error_, this, std::placeholders::_1);
        wss_client_->onmessage = std::bind(&simple_websocket_impl::on_message_, this, std::placeholders::_1);
    }

    virtual void close() override
    {
        wss_client_.reset();
    }

    virtual void send_message(const std::string &message) override
    {
        auto send_stream = std::make_shared<WssClient::SendStream>();
        *send_stream << message;
        wss_client_->send(send_stream);
    }


private:
    simple_websocket *delegate_;

    void on_open_()
    {
        if (delegate_->on_open)
        {
            delegate_->on_open();
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

    std::unique_ptr<WssClient> wss_client_;
};


simple_websocket::simple_websocket()
        : impl_{new simple_websocket_impl{this}}
{ }

void slack::simple_websocket::open(const std::string &url)
{
    impl_->open(url);
}

void slack::simple_websocket::close()
{
    impl_->close();
}

void slack::simple_websocket::send_message(const std::string &message)
{
    impl_->send_message(message);
}

} //namespace slack

