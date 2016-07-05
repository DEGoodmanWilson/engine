//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <cpr/cpr.h>
#include "environment.h"

::Environment* env;

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    env = dynamic_cast<::Environment*>(::testing::AddGlobalTestEnvironment(new ::Environment(std::getenv("SLACK_TOKEN"))));

    return RUN_ALL_TESTS();
}
