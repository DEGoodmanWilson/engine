//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>

class Environment : public ::testing::Environment
{
    virtual void SetUp() override
    {
    }

    virtual void TearDown() override
    {
    }

};

int main(int argc, char **argv) {
    if (argc != 2)
    {
        std::cout << "USAGE: " << argv[0] << " xoxb-token-here" << std::endl;
        exit(-1);
    }

    std::string token = argv[1];

    slack::set_token(token);


    ::testing::InitGoogleTest(&argc, argv);

    ::testing::AddGlobalTestEnvironment(new Environment());

    return RUN_ALL_TESTS();
}
