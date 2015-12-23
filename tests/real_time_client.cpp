//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>


class websocket : public slack::websocket
{

public:
    void receive_message(const std::string &message)
    {
        this->on_message(message);
    }


    void open(const std::string &url) override
    {}

    virtual void close() override
    {}

    virtual void send_message(const std::string &message) override
    {}
};

//TODO tests for real time pinging!

TEST(rtm, hello)
{
    std::string event_str = R"(
    {
        "type": "hello"
    }
    )";

    auto socket = std::make_shared<websocket>();

    slack::real_time_client client{socket, "wss://fobar"};
//    client.register_event_handler(slack::event::hello::type, [](std::shared_ptr<slack::base::event> event){
//       ASSERT_TRUE(static_cast<bool>(event));
//    });
    client.register_event_handler<slack::event::hello>([](std::shared_ptr<slack::event::hello> event){
       ASSERT_TRUE(static_cast<bool>(event));
    });

    socket->receive_message(event_str);
}


TEST(rtm, user_typing)
{
    std::string event_str = R"(
    {
        "type": "user_typing",
        "channel": "C02ELGNBH",
        "user": "U024BE7LH"
    }
    )";

    auto socket = std::make_shared<websocket>();

    slack::real_time_client client{socket, "wss://fobar"};
    client.register_event_handler<slack::event::user_typing>([](std::shared_ptr<slack::event::user_typing> event){
        ASSERT_TRUE(static_cast<bool>(event));
        ASSERT_EQ("C02ELGNBH", *event->channel);
        ASSERT_EQ("U024BE7LH", *event->user);
    });
    socket->receive_message(event_str);
}

/***
        //set up Websocket client
        slack::websocket::open = [](const std::string &url) {
            wss_client_ = new SimpleWeb::SocketClient<SimpleWeb::WSS>(std::string{url}.erase(0, 6), false);
//            wss_client_->onopen = std::bind(&real_time_client::on_open_, this);
//            wss_client_->onclose = std::bind(&real_time_client::on_close_,
//                                            this,
//                                            std::placeholders::_1,
//                                            std::placeholders::_2);
//            wss_client_->onerror = std::bind(&real_time_client::on_error_, this, std::placeholders::_1);
//            wss_client_->onmessage = std::bind(&real_time_client::on_message_, this, std::placeholders::_1);
        };

        slack::websocket::close = []() {
            wss_client_.reset();
        };

        slack::websocket::send_message = [](const std::string &message) {
            if (wss_client_)
            {
                auto send_stream = std::make_shared<WssClient::SendStream>();
                *send_stream << message;
                wss_client_->send(send_stream);
            }
        }
***/
