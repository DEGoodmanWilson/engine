//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>

//really hard to test this without an app…
TEST(oauth_access, oauth_access_failure)
{
    auto result = slack::oauth::access("hahaha", "nope", "you've got to be kidding me", slack::oauth::parameter::access::redirect_uri{"http://example.com"});
    ASSERT_FALSE(result);
    ASSERT_EQ(slack::oauth::response::error::access::INVALID_CLIENT_ID, result.error.value());
}
