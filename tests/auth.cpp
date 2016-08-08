//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include "environment.h"

TEST(auth, auth_test_basic)
{
    auto result = env->slack.auth.test();
    ASSERT_TRUE(result);
}

TEST(auth, auth_test_fail)
{
    auto token = env->slack.token();
    env->slack.reset_token("nope");
    auto result = env->slack.auth.test();
    ASSERT_FALSE(result);
    ASSERT_EQ(slack::auth::test::error::INVALID_AUTH, result.error_message);
    env->slack.reset_token(token);
}