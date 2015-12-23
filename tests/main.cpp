//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <cpr.h>
#include <Simple-WebSocket-Server/client_wss.hpp>

class Environment :
        public ::testing::Environment
{
public:
    virtual void SetUp() override
    {
//        //set up HTTP client
//        slack::http::get = [](std::string url, slack::http::params params) -> slack::http::response {
//            cpr::Parameters p;
//            for (auto &kv : params)
//            {
//                p.AddParameter({kv.first, kv.second});
//            }
//
//            auto response = cpr::Get(cpr::Url{url}, p);
//
//            return {static_cast<uint32_t>(response.status_code), response.text};
//        };
//
//        slack::http::post = [](std::string url, slack::http::params params) -> slack::http::response {
//            cpr::Parameters p;
//            for (auto &kv : params)
//            {
//                p.AddParameter({kv.first, kv.second});
//            }
//
//            auto response = cpr::Post(cpr::Url{url}, p);
//
//            return {static_cast<uint32_t>(response.status_code), response.text};
//        };


    }

    virtual void TearDown() override
    {
    }

private:
    std::unique_ptr<SimpleWeb::SocketClient<SimpleWeb::WSS>> wss_client_;
    std::unique_ptr<slack::real_time_client> rtm_client;
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
