//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>


class Environment :
        public ::testing::Environment
{
public:
    Environment(const std::string& token) :slack{token} {}
    virtual void SetUp() override
    {
    }

    virtual void TearDown() override
    {
    }

    slack::web_client slack;
};

extern ::Environment* env;