//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include "environment.h"

TEST(api, api_test_basic)
{
    auto result = env->slack.api.test();
    ASSERT_TRUE(result);
    ASSERT_TRUE(result.success());
}

TEST(api, api_with_lvalue_parameters)
{
    slack::api::test::parameter::error e{"error"};
    slack::api::test::parameter::foo f{"bar"};

    auto result = env->slack.api.test(e, f);
    ASSERT_FALSE(result);
    ASSERT_EQ("bar", result.args["foo"]);
    ASSERT_EQ("error", result.error_message);
}

TEST(api, api_with_rvalue_parameters)
{
    auto result = env->slack.api.test(slack::api::test::parameter::foo{"bar"}, slack::api::test::parameter::error{"error"});
    ASSERT_FALSE(result);
    ASSERT_EQ("bar", result.args["foo"]);
    ASSERT_EQ("error", result.error_message);
}

TEST(api, http_transport_failure)
{
    auto old_uri = env->slack.get_uri();
    env->slack.set_uri("http://google.com/");
    auto result = env->slack.api.test();
    env->slack.set_uri(old_uri);
    ASSERT_FALSE(result);
    ASSERT_EQ("404", result.error_message);
}