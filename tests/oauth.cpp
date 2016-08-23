//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <luna/luna.h>
#include "environment.h"

extern std::string token;

//really hard to test this without an app…
TEST(oauth_access, oauth_access_failure)
{
    auto result = env->slack.oauth.access("hahaha", "nope", "you've got to be kidding me", slack::oauth::access::parameter::redirect_uri{"http://example.com"});
    ASSERT_FALSE(result);
    ASSERT_EQ(slack::oauth::access::error::INVALID_CLIENT_ID, result.error_message);
}

//Testing success requires us to run a webserver…
TEST(oauth_access, oauth_access_success)
{

    luna::server server;
    server.handle_request(luna::request_method::GET, "/oauth.access", [](const auto& req) -> luna::response
        {
            return {R"(
{
    "ok": true,
    "access_token": "xoxp-1234",
    "scope": "identify,bot",
    "user_id": "U1234",
    "team_name": "foobar",
    "team_id": "T1234",
    "bot": {
        "bot_user_id": "U1232",
        "bot_access_token": "xoxb-1234"
    }
}
            )"};
        });

    auto original_uri = slack::slack::get_uri();
    slack::slack::set_uri("http://localhost:8080/");

    auto result = env->slack.oauth.access("hahaha", "nope", "you've got to be kidding me", slack::oauth::access::parameter::redirect_uri{"http://example.com"});
    ASSERT_TRUE(result);

    slack::slack::set_uri(original_uri);
}