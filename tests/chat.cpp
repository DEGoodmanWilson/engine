//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>

class chat_env : public ::testing::Test
{
public:
    chat_env()
    {
        //we need a channel. I have a test channel in my team called "donbot-messages". YMMV.
        auto result = slack::channels::list();
        for(const auto c : result.channels.value())
        {
            if(c.name == "donbot-messages")
            {
                channel_id = c.id;
                break;
            }
        }
    }

    slack::channel_id channel_id;
};

slack::ts ts;


TEST_F(chat_env, chat_post_basic)
{
    std::string message = "this is a test";
    auto result = slack::chat::post_message(channel_id, message);
    ASSERT_TRUE(result);
    ASSERT_EQ(message, result.message->text);
    ts = result.message->ts;
}

//this one is going to fail for now. Probably.
TEST_F(chat_env, chat_update_basic)
{
    std::string new_message = "This is not a test";
    auto result = slack::chat::update(ts, channel_id, new_message);
    ASSERT_TRUE(result);
    ASSERT_EQ(new_message, result.text.value());
}

//this one is going to fail for now. Probably.
TEST_F(chat_env, chat_delete_basic)
{
    auto result = slack::chat::delete_it(ts, channel_id);
    ASSERT_TRUE(result);
}