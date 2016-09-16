//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <chrono>

//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <chrono>

TEST(http_event_client, hello)
{
    std::string event_str = R"(
    {
            "token": "WHYYES",
            "team_id": "T123",
            "api_app_id": "A123",
            "event": {
                    "type": "hello"
            },
            "type": "event_callback",
            "authed_users": [
                    "U123"
            ]
    }
    )";

    slack::http_event_client handler{[](const auto &id)
                                         { return "xoxb-123"; }, "WHYYES"};

    bool received = false;

    handler.on<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event,
                                        const slack::http_event_envelope &envelope)
                                        {
                                            EXPECT_TRUE(static_cast<bool>(event));
                                            received = ((envelope.token == "WHYYES")
                                                        && (envelope.team_id == "T123")
                                                        && (envelope.api_app_id == "A123")
                                                        && (envelope.authed_users.size() == 1)
                                                        && (envelope.authed_users[0] == "U123"));
                                        });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
}

TEST(http_event_client, unknown_event)
{
    std::string event_str = R"(
    {
            "token": "WHYYES",
            "team_id": "T123",
            "api_app_id": "A123",
            "event": {
                    "type": "WATWAT"
            },
            "type": "event_callback",
            "authed_users": [
                    "U123"
            ]
    }
    )";

    slack::http_event_client handler{[](const auto &id)
                                         { return "xoxb-123"; }, "WHYYES"};

    bool received = false;
    std::string type = "";

    handler.on<slack::event::unknown>([&](std::shared_ptr<slack::event::unknown> event,
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

    slack::http_event_client handler{[](const auto &id)
                                         { return "xoxb-123"; }, "abcdefg"};

    bool received = false;
    std::string whatwegot = "";

    handler.on_error([&](std::string &&message,
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

    slack::http_event_client handler{[](const auto &id)
                                         { return "xoxb-123"; }, "abcdefg"};

    bool received = false;
    std::string whatwegot = "";

    handler.on_error([&](std::string &&message,
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

    slack::http_event_client handler{[](const auto &id)
                                         { return "xoxb-123"; }, "WHYYES"};

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
            "type": "event_callback",
            "authed_users": [
                    "U123"
            ]
    }
    )";

    slack::http_event_client handler{[](const auto &id)
                                         { return "xoxb-123"; }, "WHYYES"};

    bool received = false;

    handler.on<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event,
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
            "type": "event_callback",
            "authed_users": [
                    "U123"
            ]
    }
    )";

    slack::http_event_client handler{[](const auto &id)
                                         { return "xoxb-123"; }, "WHYYES"};

    bool received = false;
    bool handled = false;

    handler.on<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event,
                                        const slack::http_event_envelope &envelope)
                                        {
                                            received = true;
                                        });
    handler.on_error([&](std::string &&message, const std::string received_json)
                         {
                             EXPECT_EQ("Invalid token on event", message);
                             handled = true;
                         });


    handler.handle_event(event_str);

    ASSERT_FALSE(received);
    ASSERT_TRUE(handled);
}

TEST(http_event_client, message_handle_success)
{
    std::string event_str = R"(
    {
            "token": "WHYYES",
            "team_id": "T123",
            "api_app_id": "A123",
            "event": {
                "type": "message",
                "user": "U123",
                "text": "More!",
                "ts": "1472014386.000092",
                "channel": "C123",
                "event_ts": "1472014386.000092"
            },
            "type": "event_callback",
            "authed_users": [
                    "U123"
            ]
    }
    )";

    slack::http_event_client handler{[](const auto &id)
                                         { return "xoxb-123"; }, "WHYYES"};

    bool received = false;
    bool handled = false;

    handler.on<slack::event::message>([&](auto event, auto envelope)
                                        {
                                            received = true;
                                        });
    handler.hears("More!", [&](auto message)
        {
            handled = true;
        });


    handler.handle_event(event_str);

    ASSERT_TRUE(received);
    ASSERT_TRUE(handled);
}

TEST(http_event_client, bot_message_handle_success)
{
    std::string event_str = R"(
    {
            "token": "WHYYES",
            "team_id": "T123",
            "api_app_id": "A123",
            "event": {
                "type": "message",
                "subtype": "bot_message",
                "bot_id": "B123",
                "username": "bot",
                "icons": {},
                "text": "More!",
                "ts": "1472014386.000092",
                "channel": "C123",
                "event_ts": "1472014386.000092"
            },
            "type": "event_callback",
            "authed_users": [
                    "B123"
            ]
    }
    )";

    slack::http_event_client handler{[](const auto &id)
                                     { return "xoxb-123"; }, "WHYYES"};

    bool received = false;
    bool handled = false;

    handler.on<slack::event::message_bot_message>([&](auto event, auto envelope)
                                      {
                                          received = true;
                                      });
    handler.hears("More!", [&](auto message)
    {
        handled = true;
    });


    handler.handle_event(event_str);

    ASSERT_TRUE(received);
    ASSERT_TRUE(handled);
}