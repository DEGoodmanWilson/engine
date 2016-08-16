//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <chrono>

TEST(rtm_event_client, hello)
{
    std::string event_str = R"(
    {
        "type": "hello"
    }
    )";

    slack::rtm_event_client handler;

    bool received = false;

    handler.register_event_handler<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event)
                                                            {
                                                                EXPECT_TRUE(static_cast<bool>(event));
                                                                received = true;
                                                            });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
}

TEST(rtm_event_client, unknown_event)
{
    std::string event_str = R"(
    {
        "type": "WATWAT"
    }
    )";

    slack::rtm_event_client handler;

    bool received = false;
    std::string type = "";

    handler.register_event_handler<slack::event::unknown>([&](std::shared_ptr<slack::event::unknown> event)
                                                              {
                                                                  EXPECT_TRUE(static_cast<bool>(event));
                                                                  received = true;
                                                                  type = event->type;
                                                              });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
    ASSERT_EQ("WATWAT", type);
}

TEST(rtm_event_client, non_event)
{
    std::string event_str = R"(
    [
        "OMG",
        "NOT AN EVENT!",
        "NOT EVEN AN OBJECT!"
    ]
    )";

    slack::rtm_event_client handler;

    bool received = false;
    std::string whatwegot = "";

    handler.register_error_handler([&](std::string &&message,
                                       const std::string received_json)
                                       {
                                           received = true;
                                           whatwegot = received_json;
                                           EXPECT_EQ("Invalid event JSON", message);
                                       });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
    ASSERT_EQ(event_str, whatwegot);
}

TEST(rtm_event_client, non_json)
{
    std::string event_str = R"(
    [ { fdsjk 234 ]] "why no
    )";

    slack::rtm_event_client handler;

    bool received = false;
    std::string whatwegot = "";

    handler.register_error_handler([&](std::string &&message,
                                       const std::string received_json)
                                       {
                                           received = true;
                                           whatwegot = received_json;
                                           EXPECT_EQ("JSON parse error", message);
                                       });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
    ASSERT_EQ(event_str, whatwegot);
}
