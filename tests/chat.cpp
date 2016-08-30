//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include "environment.h"

class chat_env : public ::testing::Test
{
public:
    chat_env()
    {
        //we need a channel. I will use #general. YMMV.
        auto result = env->slack.channels.list();
        for(const auto c : result.channels.value())
        {
            if(c.name == "general")
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
    auto result = env->slack.chat.postMessage(channel_id, message, slack::chat::postMessage::parameter::as_user{true}, slack::chat::postMessage::parameter::icon_url{"http://iosicongallery.com/iosicongallery/img/512/slack-2014.png"});
    ASSERT_TRUE(result);
    ASSERT_TRUE(static_cast<bool>(result.message));
    ASSERT_EQ(message, result.message->text);
    ts = result.message->ts;
}

//this one is going to fail for now. Probably.
TEST_F(chat_env, chat_update_basic)
{
    std::string new_message = "This is not a test";
    auto result = env->slack.chat.update(ts, channel_id, new_message);
    ASSERT_TRUE(result);
    ASSERT_EQ(new_message, result.text.value());
}

//this one is going to fail for now. Probably.
TEST_F(chat_env, chat_delete_basic)
{
    auto result = env->slack.chat.delete_it(ts, channel_id);
    ASSERT_TRUE(result);
}