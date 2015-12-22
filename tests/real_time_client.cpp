//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>


//TODO tests for real time pinging!

TEST(rtm, hello)
{
    std::string event_str = R"(
    {
        "type": "hello"
    }
    )";

    slack::real_time_client client{"wss://fobar"};
//    client.register_event_handler(slack::event::hello::type, [](std::shared_ptr<slack::base::event> event){
//       ASSERT_TRUE(static_cast<bool>(event));
//    });
    client.register_event_handler<slack::event::hello>([](std::shared_ptr<slack::event::hello> event){
       ASSERT_TRUE(static_cast<bool>(event));
    });
    client.handle_event_from_slack(event_str);
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

    slack::real_time_client client{"wss://fobar"};
    client.register_event_handler<slack::event::user_typing>([](std::shared_ptr<slack::event::user_typing> event){
        ASSERT_TRUE(static_cast<bool>(event));
        ASSERT_EQ("C02ELGNBH", *event->channel);
        ASSERT_EQ("U024BE7LH", *event->user);
    });
    client.handle_event_from_slack(event_str);
}