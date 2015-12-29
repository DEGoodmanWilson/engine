//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/websocket.h"

#include <Simple-WebSocket-Server/client_wss.hpp>

namespace slack
{

class simple_websocket::simple_websocket_impl :
        public websocket
{

    using WssClient = SimpleWeb::SocketClient<SimpleWeb::WSS>;


public:
    simple_websocket_impl(simple_websocket *delegate) :
            delegate_{delegate}
    { }


    virtual void start(const std::string& url) override
    {
        wss_client_.reset(new WssClient{std::string{url}.erase(0, 6), false}); //TODO true

        wss_client_->onopen = std::bind(&simple_websocket_impl::on_connect_, this);
        wss_client_->onclose = std::bind(&simple_websocket_impl::on_close_,
                                        this,
                                        std::placeholders::_1,
                                        std::placeholders::_2);
        wss_client_->onerror = std::bind(&simple_websocket_impl::on_error_asio_, this, std::placeholders::_1);
        wss_client_->onmessage = std::bind(&simple_websocket_impl::on_message_, this, std::placeholders::_1);

        try
        {
            wss_client_->start();
        }
        catch(std::invalid_argument e)
        {
//            std::cout << e.what() << std::endl;
            //we don't get the entire error_code, obnoxously
            on_error_(websocket::error_code::NETWORK_ERROR);
        }
    }

    virtual void stop() override
    {
        if(wss_client_)
        {
            wss_client_->stop();
        }
    }

    virtual void send_message(const std::string &message) override
    {
        if(wss_client_)
        {
            auto send_stream = std::make_shared<WssClient::SendStream>();
            *send_stream << message;
            wss_client_->send(send_stream);
        }
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
            delegate_->on_close(websocket::close_reason::UNKNOWN);
        }
    }

    void on_error_(websocket::error_code code)
    {
        if(delegate_->on_error)
        {
            delegate_->on_error(code);
        }
    }

    void on_error_asio_(const boost::system::error_code &error_code)
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

simple_websocket::~simple_websocket() = default;

void slack::simple_websocket::start(const std::string& url)
{
    impl_->start(url);
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

