//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>


TEST(api, api_test_basic)
{
    auto result = slack::api::test();
    ASSERT_TRUE(result);
    ASSERT_EQ(std::experimental::nullopt, result.args);
    ASSERT_EQ(std::experimental::nullopt, result.error);
}

TEST(api, api_with_lvalue_parameters)
{
    slack::api::parameter::test::error e{"error"};
    slack::api::parameter::test::foo f{"bar"};

    auto result = slack::api::test(e, f);
    ASSERT_FALSE(static_cast<bool>(result));
    ASSERT_EQ("bar", result.args.value()["foo"]);
    ASSERT_EQ("error", result.error.value());
}

TEST(api, api_with_rvalue_parameters)
{
    auto result = slack::api::test(slack::api::parameter::test::foo{"bar"}, slack::api::parameter::test::error{"error"});
    ASSERT_FALSE(static_cast<bool>(result));
    ASSERT_EQ("bar", result.args.value()["foo"]);
    ASSERT_EQ("error", result.error.value());
}