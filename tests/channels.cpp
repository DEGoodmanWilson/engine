//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>


TEST(channels, channel_list_basic)
{
    auto result = slack::channels::list();
    ASSERT_TRUE(result);
    ASSERT_GT(result.channels->size(), 0); //in most cases it will be at least 2 (#general and #random)
}