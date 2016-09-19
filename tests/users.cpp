//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include "environment.h"

//class users_info : public ::testing::Test
//{
//public:
//    users_info()
//    {
//        //we need a user_id. I will use @don. YMMV.
//        auto result = env->slack.users.list();
//        for(const auto c : result.channels.value())
//        {
//            if(c.name == "general")
//            {
//                channel_id = c.id;
//                break;
//            }
//        }
//    }
//
//    slack::channel_id channel_id;
//};

//this one is going to fail for now. Probably.
TEST(users_info, users_info_basic)
{
    auto result = env->slack.users.info("XYZ");
    ASSERT_FALSE(result);
}