//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <chrono>

//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <chrono>

TEST(http_event_client, hello)
{
    std::string event_str = R"(
    {
            "token": "WHYNO",
            "team_id": "T123",
            "api_app_id": "A123",
            "event": {
                    "type": "hello"
            },
            "event_ts": "1234567890.123456",
            "type": "event_callback",
            "authed_users": [
                    "U123"
            ]
    }
    )";

    slack::http_event_client handler{"abcdefg"};

    bool received = false;

    handler.register_event_handler<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event,
                                                            const slack::http_event_envelope &envelope)
                                                            {
                                                                EXPECT_TRUE(static_cast<bool>(event));
                                                                received = true;
                                                            });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
}

TEST(http_event_client, unknown_event)
{
    std::string event_str = R"(
    {
            "token": "WHYNO",
            "team_id": "T123",
            "api_app_id": "A123",
            "event": {
                    "type": "WATWAT"
            },
            "event_ts": "1234567890.123456",
            "type": "event_callback",
            "authed_users": [
                    "U123"
            ]
    }
    )";

    slack::http_event_client handler{"abcdefg"};

    bool received = false;
    std::string type = "";

    handler.register_event_handler<slack::event::unknown>([&](std::shared_ptr<slack::event::unknown> event,
                                                              const slack::http_event_envelope &envelope)
                                                              {
                                                                  EXPECT_TRUE(static_cast<bool>(event));
                                                                  received = true;
                                                                  type = event->type;
                                                              });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
    ASSERT_EQ("WATWAT", type);
}

TEST(http_event_client, non_event)
{
    std::string event_str = R"(
    [
        "OMG",
        "NOT AN EVENT!",
        "NOT EVEN AN OBJECT!"
    ]
    )";

    slack::http_event_client handler{"abcdefg"};

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

TEST(http_event_client, non_json)
{
    std::string event_str = R"(
    [ { fdsjk 234 ]] "why no
    )";

    slack::http_event_client handler{"abcdefg"};

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

TEST(http_event_client, url_verification)
{
    std::string event_str = R"(
    {
            "token": "WHYYES",
            "type": "url_verification",
            "challenge": "foobar"
    }
    )";

    slack::http_event_client handler{"WHYYES"};

    auto response = handler.handle_event(event_str);

    ASSERT_EQ("foobar", response);
}

TEST(http_event_client, token_match)
{
    std::string event_str = R"(
    {
            "token": "WHYYES",
            "team_id": "T123",
            "api_app_id": "A123",
            "event": {
                    "type": "hello"
            },
            "event_ts": "1234567890.123456",
            "type": "event_callback",
            "authed_users": [
                    "U123"
            ]
    }
    )";

    slack::http_event_client handler{"WHYYES"};

    bool received = false;

    handler.register_event_handler<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event,
                                                            const slack::http_event_envelope &envelope)
                                                            {
                                                                EXPECT_TRUE(static_cast<bool>(event));
                                                                EXPECT_EQ("WHYYES", envelope.token);
                                                                received = ("WHYYES" == envelope.token);
                                                            });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
}

TEST(http_event_client, token_mismatch)
{
    std::string event_str = R"(
    {
            "token": "WHYNO",
            "team_id": "T123",
            "api_app_id": "A123",
            "event": {
                    "type": "hello"
            },
            "event_ts": "1234567890.123456",
            "type": "event_callback",
            "authed_users": [
                    "U123"
            ]
    }
    )";

    slack::http_event_client handler{"WHYYES"};

    bool received = false;
    bool handled = false;

    handler.register_event_handler<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event,
                                                            const slack::http_event_envelope &envelope)
                                                            {
                                                                received = true;
                                                            });
    handler.register_error_handler([&](std::string &&message, const std::string received_json)
                                       {
                                           EXPECT_EQ("Invalid token on event", message);
                                           handled = true;
                                       });


    handler.handle_event(event_str);

    ASSERT_FALSE(received);
    ASSERT_TRUE(handled);
}