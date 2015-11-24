//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>


TEST(auth, auth_test_basic)
{
    auto result = slack::auth::test();
    ASSERT_TRUE(static_cast<bool>(result));
}