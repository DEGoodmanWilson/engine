//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
static_cast<uint32_t>(response.status_code)

class Environment :
        public ::testing::Environment
{
    virtual void SetUp() override
    {
        slack::http::get = [](std::string url, slack::http::params params) -> slack::http::response {
            cpr::Parameters p;
            for (auto &kv : params)
            {
                p.AddParameter({kv.first, kv.second});
            }

            auto response = cpr::Get(cpr::Url{url}, p);

            return {static_cast<uint32_t>(response.status_code), response.text};
        };

        slack::http::post = [](std::string url, slack::http::params params) -> slack::http::response {
            cpr::Parameters p;
            for (auto &kv : params)
            {
                p.AddParameter({kv.first, kv.second});
            }

            auto response = cpr::Post(cpr::Url{url}, p);

            return {static_cast<uint32_t>(response.status_code), response.text};
        };

    }

    virtual void TearDown() override
    {
    }

};

std::string token;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "USAGE: " << argv[0] << " xoxb-token-here" << std::endl;
        exit(-1);
    }

    token = argv[1];

    slack::set_token(token);


    ::testing::InitGoogleTest(&argc, argv);

    ::testing::AddGlobalTestEnvironment(new Environment());

    return RUN_ALL_TESTS();
}
