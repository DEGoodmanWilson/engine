//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <random>
#include "environment.h"

extern std::string token;

slack::channel_id id;

TEST(channels, channels_list_basic)
{
    auto result = env->slack.channels.list();
    ASSERT_TRUE(*result);
    ASSERT_LT(0, result->channels->size()); //in most cases it will be at least 2 (#general and #random)
}

TEST(channels, channels_create_basic)
{
    std::string name = "tc";
    auto result = env->slack.channels.create(name);
    ASSERT_TRUE(*result);
    ASSERT_TRUE(static_cast<bool>(result->channel));
    slack::channel chan{*result->channel};
    //TODO store the ID so we can delete its
    id = chan.id;
    ASSERT_EQ(name, chan.name);
}

//TODO shouldn't depend upon id stored in last test! Should find it anew!
TEST(channels, channels_rename_basic)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis{};
    int rand = dis(gen);
    std::string new_name = "tc-"+std::to_string(rand);
    auto result = env->slack.channels.rename(id, new_name);
    ASSERT_TRUE(*result);
    slack::channel chan{*result->channel};
    ASSERT_EQ(new_name, chan.name);
}

TEST(channels, channels_archive_basic)
{
    auto result = env->slack.channels.archive(id);
    ASSERT_TRUE(*result);
    //really not much else we can check here.
}