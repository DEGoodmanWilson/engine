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
    ASSERT_LT(0, result.channels->size()); //in most cases it will be at least 2 (#general and #random)
}

TEST(channels, channels_create_basic)
{
    std::string name = "donbot-test-channel";
    auto result = slack::channels::create(name);
    ASSERT_TRUE(result);
    ASSERT_TRUE(static_cast<bool>(result.channel));
    slack::channel chan{*result.channel};
    //TODO store the ID so we can delete its
    id = chan.id;
    ASSERT_EQ(name, chan.name);
}

TEST(channels, channels_archive_basic)
{
    auto result = slack::channels::archive(id);
    ASSERT_TRUE(result);
    //really not much else we can check here.
}