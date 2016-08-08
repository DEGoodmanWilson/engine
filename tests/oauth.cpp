//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include "environment.h"

extern std::string token;

//really hard to test this without an app…
TEST(oauth_access, oauth_access_failure)
{
    auto result = env->slack.oauth.access("hahaha", "nope", "you've got to be kidding me", slack::oauth::access::parameter::redirect_uri{"http://example.com"});
    ASSERT_FALSE(result);
    ASSERT_EQ(slack::oauth::access::error::INVALID_CLIENT_ID, result.error_message);
}
