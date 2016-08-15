//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <chrono>

TEST(event_handler, hello)
{
    std::string event_str = R"(
    {
        "type": "hello"
    }
    )";

    slack::event::event_handler handler;

    bool received = false;

    handler.register_event_handler<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event) {
        EXPECT_TRUE(static_cast<bool>(event));
        received = true;
    });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
}

TEST(event_handler, unknown_event)
{
    std::string event_str = R"(
    {
        "type": "WATWAT"
    }
    )";

    slack::event::event_handler handler;

    bool received = false;
    std::string type = "";

    handler.register_event_handler<slack::event::unknown>([&](std::shared_ptr<slack::event::unknown> event) {
            EXPECT_TRUE(static_cast<bool>(event));
            received = true;
            type = event->type;
        });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
    ASSERT_EQ("WATWAT", type);
}

TEST(event_handler, non_event)
{
    std::string event_str = R"(
    [
        "OMG",
        "NOT AN EVENT!",
        "NOT EVEN AN OBJECT!"
    ]
    )";

    slack::event::event_handler handler;

    bool received = false;
    std::string whatwegot = "";

    handler.register_error_handler([&](std::string &&message, const std::string received_json) {
            received = true;
            whatwegot = received_json;
            EXPECT_EQ("Invalid event JSON", message);
        });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
    ASSERT_EQ(event_str, whatwegot);
}

TEST(event_handler, non_json)
{
    std::string event_str = R"(
    [ { fdsjk 234 ]] "why no
    )";

    slack::event::event_handler handler;

    bool received = false;
    std::string whatwegot = "";

    handler.register_error_handler([&](std::string &&message, const std::string received_json) {
            received = true;
            whatwegot = received_json;
            EXPECT_EQ("JSON parse error", message);
        });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
    ASSERT_EQ(event_str, whatwegot);
}

TEST(event_handler, token_match)
{
    std::string event_str = R"(
    {
        "type": "hello",
        "token": "whyyes"
    }
    )";

    slack::event::event_handler handler{"whyyes"};

    bool received = false;

    handler.register_event_handler<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event) {
            EXPECT_TRUE(static_cast<bool>(event));
            EXPECT_TRUE(static_cast<bool>(event->token));
            EXPECT_EQ("whyyes", *(event->token));
            received = ("whyyes" == *event->token);
        });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
}

TEST(event_handler, token_mismatch)
{
    std::string event_str = R"(
    {
        "type": "hello",
        "token": "whyno"
    }
    )";

    slack::event::event_handler handler{"whyyes"};

    bool received = false;
    bool handled = false;

    handler.register_event_handler<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event) {
            received = true;
        });
    handler.register_error_handler([&](std::string &&message, const std::string received_json) {
            EXPECT_EQ("Invalid token on event", message);
            handled = true;
        });


    handler.handle_event(event_str);

    ASSERT_FALSE(received);
    ASSERT_TRUE(handled);
}