//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>


TEST(api, api_test_basic)
{
    auto result = slack::api::test();
    ASSERT_TRUE(result.ok);
    ASSERT_TRUE(static_cast<bool>(result));
    ASSERT_EQ(result.args, std::experimental::nullopt);
    ASSERT_EQ(result.error, std::experimental::nullopt);
}

TEST(api, api_with_lvalue_parameters)
{
    slack::api::parameter::test::error e{"error"};
    slack::api::parameter::test::foo f{"bar"};

    auto result = slack::api::test(e, f);
    ASSERT_FALSE(result.ok); //because we requested an error condition
    ASSERT_EQ(result.args.value()["foo"], "bar");
    ASSERT_EQ(result.error_str.value(), "error");
}

TEST(api, api_with_rvalue_parameters)
{
    auto result = slack::api::test(slack::api::parameter::test::foo{"bar"}, slack::api::parameter::test::error{"error"});
    ASSERT_FALSE(result.ok);
    ASSERT_EQ(result.args.value()["foo"], "bar");
    ASSERT_EQ(result.error_str.value(), "error");
}