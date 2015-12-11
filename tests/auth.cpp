//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>

extern std::string token;

TEST(auth, auth_test_basic)
{
    auto result = slack::auth::test();
    ASSERT_TRUE(result);
}

TEST(auth, auth_test_fail)
{
    slack::set_token("BADTOKEN");
    auto result = slack::auth::test();
    ASSERT_FALSE(result);
    ASSERT_EQ(slack::auth::test::error::INVALID_AUTH, result.error_message);
    //need to reset token. Should do this RIAA style /shrug
    slack::set_token(token);
}