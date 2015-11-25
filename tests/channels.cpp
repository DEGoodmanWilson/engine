//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>

slack::channel_id id;

TEST(channels, channels_list_basic)
{
    auto result = slack::channels::list();
    ASSERT_TRUE(result);
    ASSERT_GT(result.channels->size(), 0); //in most cases it will be at least 2 (#general and #random)
}

TEST(channels, channels_create_basic)
{
    std::string name = "donbot-test-channel";
    auto result = slack::channels::create(slack::channels::parameter::create::name{name});
    ASSERT_TRUE(result);
    slack::channel chan = result.channel;
    //TODO store the ID so we can delete it
    id = chan.id;
    ASSERT_EQ(chan.name, name);
}