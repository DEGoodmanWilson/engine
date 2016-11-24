//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include "environment.h"

class users_info : public ::testing::Test
{
public:
    users_info()
    {
        //we need a user_id. I will use @don. YMMV.
        auto result = env->slack.users.list();
        for(const auto &u : result.members)
        {
            if(u.name == "don")
            {
                user_id = u.id;
                break;
            }
        }
    }

    slack::user_id user_id;
};

TEST_F(users_info, users_info_fail)
{
    auto result = env->slack.users.info("XYZ");
    ASSERT_FALSE(result);
    ASSERT_EQ(slack::users::info::error::USER_NOT_FOUND, result.error_message);
}

TEST_F(users_info, users_info_basic)
{
    auto result = env->slack.users.info(user_id);
    ASSERT_TRUE(result);
    ASSERT_EQ("don", result.user.name);
}