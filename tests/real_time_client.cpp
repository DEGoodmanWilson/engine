//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>


class websocket :
        public slack::websocket
{

public:
    void receive_message(const std::string &message)
    {
        this->on_message(message);
    }


    virtual void start() override
    { }

    virtual void stop() override
    { }

    virtual void send_message(const std::string &message) override
    { }
};


TEST(rtm, hello)
{
    std::string event_str = R"(
    {
        "type": "hello"
    }
    )";

    auto socket = std::make_shared<websocket>();

    slack::real_time_client client{socket};
//    client.register_event_handler(slack::event::hello::type, [](std::shared_ptr<slack::base::event> event){
//       ASSERT_TRUE(static_cast<bool>(event));
//    });
    client.register_event_handler<slack::event::hello>([](std::shared_ptr<slack::event::hello> event) {
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

    slack::real_time_client client{socket};
    client.register_event_handler<slack::event::user_typing>([](std::shared_ptr<slack::event::user_typing> event) {
        ASSERT_TRUE(static_cast<bool>(event));
        ASSERT_EQ("C02ELGNBH", *event->channel);
        ASSERT_EQ("U024BE7LH", *event->user);
    });
    socket->receive_message(event_str);
}

TEST(rtm, actually_connect)
{
    auto resp = slack::rtm::start();
    auto socket = std::make_shared<slack::simple_websocket>(*resp.url);
    slack::real_time_client client{socket};

    //Set up a handler to handle that first hello. Notice that we, uh, really ought to time out in case we don't connect!
    client.register_event_handler<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event) {
        ASSERT_TRUE(static_cast<bool>(event));
        client.stop();
    });
}

//TODO tests for real time pinging!
