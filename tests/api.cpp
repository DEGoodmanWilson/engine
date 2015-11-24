//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <optional/optional.hpp>

class TestEnv : public ::testing::Test
{
public:
    TestEnv()
    {
    }
};

//// Tests: ////////////////////////////////////////////////////////////////////////////////////////

TEST_F(TestEnv, ApiTestBasic)
{
    auto result = slack::api::test();
    ASSERT_TRUE(result.ok);
    ASSERT_TRUE(static_cast<bool>(result));
    ASSERT_EQ(result.args, std::experimental::nullopt);
    ASSERT_EQ(result.error, std::experimental::nullopt);

//    std::cout << slack::api::test().raw_json << std::endl;
//    slack::api::parameter::test::error e{"my error"};
//    slack::api::parameter::test::foo f{"bar"};
//    std::cout << slack::api::test(e).raw_json << std::endl;
//    std::cout << slack::api::test(slack::api::parameter::test::error{"your error"}, slack::api::parameter::test::foo{"bar"}).raw_json << std::endl;
//    std::cout << slack::api::test(e, slack::api::parameter::test::foo{"bar"}).raw_json << std::endl;

}

