//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <chrono>

TEST(http_event_client, hello_threaded)
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

    slack::http_event_client handler{"WHYYES", slack::http_event_client::parameter::thread_timeout{10ms}};

    bool received = false;
    std::mutex m;
    std::condition_variable cv;

    handler.on<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event,
                                        const slack::http_event_envelope &envelope)
                                    {
                                        std::unique_lock<std::mutex> l(m);

                                        EXPECT_TRUE(static_cast<bool>(event));
                                        received = ((envelope.verification_token == "WHYYES")
                                                    && (envelope.token.team_id == "T123")
                                                    && (envelope.api_app_id == "A123")
                                                    && (envelope.authed_users.size() == 1)
                                                    && (envelope.authed_users[0] == "U123"));

                                        l.unlock();
                                        cv.notify_one();
                                    });

    handler.handle_event(event_str, {
            "T123",
            "xoxp-123",
            "U123",
            "xoxb-123",
            "B123",
    });

    std::unique_lock<std::mutex> l(m);
    cv.wait(l, [&](){return received;});
    ASSERT_TRUE(received);
}

TEST(http_event_client, hello_unthreaded)
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

    slack::http_event_client handler{"WHYYES", slack::http_event_client::parameter::thread_count{0}};

    bool received = false;
    auto thread_id = std::this_thread::get_id();

    handler.on<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event,
                                        const slack::http_event_envelope &envelope)
                                    {
                                        EXPECT_TRUE(static_cast<bool>(event));
                                        received = ((envelope.verification_token == "WHYYES")
                                                    && (envelope.token.team_id == "T123")
                                                    && (envelope.api_app_id == "A123")
                                                    && (envelope.authed_users.size() == 1)
                                                    && (envelope.authed_users[0] == "U123")
                                                    && (thread_id == std::this_thread::get_id()));
                                    });

    handler.handle_event(event_str, {
            "T123",
            "xoxp-123",
            "U123",
            "xoxb-123",
            "B123",
    });

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

    slack::http_event_client handler{"WHYYES", slack::http_event_client::parameter::thread_timeout{10ms}};

    bool received = false;
    std::string type = "";
    std::mutex m;
    std::condition_variable cv;

    handler.on<slack::event::unknown>([&](std::shared_ptr<slack::event::unknown> event,
                                          const slack::http_event_envelope &envelope)
                                      {
                                          std::unique_lock<std::mutex> l(m);

                                          EXPECT_TRUE(static_cast<bool>(event));
                                          received = true;
                                          type = event->type;

                                          l.unlock();
                                          cv.notify_one();
                                      });

    handler.handle_event(event_str, {
            "T123",
            "xoxp-123",
            "U123",
            "xoxb-123",
            "B123",
    });

    std::unique_lock<std::mutex> l(m);
    cv.wait(l, [&](){return received;});
    ASSERT_TRUE(received);
    ASSERT_EQ("WATWAT", type);
}

TEST(http_event_client, unknown_event_subtype)
{
    std::string event_str = R"(
    {
            "token": "WHYYES",
            "team_id": "T123",
            "api_app_id": "A123",
            "event": {
                    "type": "message",
                    "subtype": "nope"
            },
            "type": "event_callback",
            "authed_users": [
                    "U123"
            ]
    }
    )";

    slack::http_event_client handler{"WHYYES", slack::http_event_client::parameter::thread_timeout{10ms}};

    bool received = false;
    std::string type = "";
    std::mutex m;
    std::condition_variable cv;

    handler.on<slack::event::unknown>([&](std::shared_ptr<slack::event::unknown> event,
                                          const slack::http_event_envelope &envelope)
                                      {
                                          std::unique_lock<std::mutex> l(m);

                                          EXPECT_TRUE(static_cast<bool>(event));
                                          received = true;
                                          type = event->type;

                                          l.unlock();
                                          cv.notify_one();
                                      });

    handler.handle_event(event_str, {
            "T123",
            "xoxp-123",
            "U123",
            "xoxb-123",
            "B123",
    });

    std::unique_lock<std::mutex> l(m);
    cv.wait(l, [&](){return received;});
    ASSERT_TRUE(received);
    ASSERT_EQ("message.nope", type);
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

    slack::http_event_client handler{"WHYYES", slack::http_event_client::parameter::thread_timeout{10ms}};

    bool received = false;
    std::string whatwegot = "";
    std::mutex m;
    std::condition_variable cv;

    handler.on_error([&](std::string &&message,
                         const std::string received_json)
                     {
                         std::unique_lock<std::mutex> l(m);

                         received = true;
                         whatwegot = received_json;
                         EXPECT_EQ("Invalid event JSON", message);

                         l.unlock();
                         cv.notify_one();
                     });

    handler.handle_event(event_str, {
            "T123",
            "xoxp-123",
            "U123",
            "xoxb-123",
            "B123",
    });

    std::unique_lock<std::mutex> l(m);
    cv.wait(l, [&](){return received;});
    ASSERT_TRUE(received);
    ASSERT_EQ(event_str, whatwegot);
}

TEST(http_event_client, non_json)
{
    std::string event_str = R"(
    [ { fdsjk 234 ]] "why no
    )";

    slack::http_event_client handler{"WHYYES", slack::http_event_client::parameter::thread_timeout{10ms}};

    bool received = false;
    std::string whatwegot = "";
    std::mutex m;
    std::condition_variable cv;

    handler.on_error([&](std::string &&message,
                         const std::string received_json)
                     {
                         std::unique_lock<std::mutex> l(m);

                         received = true;
                         whatwegot = received_json;
                         EXPECT_EQ("JSON parse error", message);

                         l.unlock();
                         cv.notify_one();
                     });

    handler.handle_event(event_str, {
            "T123",
            "xoxp-123",
            "U123",
            "xoxb-123",
            "B123",
    });

    std::unique_lock<std::mutex> l(m);
    cv.wait(l, [&](){return received;});
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

    slack::http_event_client handler{"WHYYES", slack::http_event_client::parameter::thread_timeout{10ms}};

    auto response = handler.handle_event(event_str, {
            "T123",
            "xoxp-123",
            "U123",
            "xoxb-123",
            "B123",
    });

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

    slack::http_event_client handler{"WHYYES", slack::http_event_client::parameter::thread_timeout{10ms}};

    bool received = false;
    std::mutex m;
    std::condition_variable cv;

    handler.on<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event,
                                        const slack::http_event_envelope &envelope)
                                    {
                                        std::unique_lock<std::mutex> l(m);

                                        EXPECT_TRUE(static_cast<bool>(event));
                                        EXPECT_EQ("WHYYES", envelope.verification_token);
                                        received = ("WHYYES" == envelope.verification_token);

                                        l.unlock();
                                        cv.notify_one();
                                    });

    handler.handle_event(event_str, {
            "T123",
            "xoxp-123",
            "U123",
            "xoxb-123",
            "B123",
    });

    std::unique_lock<std::mutex> l(m);
    cv.wait(l, [&](){return received;});
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

    slack::http_event_client handler{"WHYYES", slack::http_event_client::parameter::thread_timeout{10ms}};

    bool received = false;
    bool handled = false;
    std::mutex m;
    std::condition_variable cv1;
    std::condition_variable cv2;

    handler.on<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event,
                                        const slack::http_event_envelope &envelope)
                                    {
                                        std::unique_lock<std::mutex> l(m);

                                        received = true;

                                        l.unlock();
                                        cv1.notify_one();
                                    });
    handler.on_error([&](std::string &&message, const std::string received_json)
                     {
                         std::unique_lock<std::mutex> l(m);

                         EXPECT_EQ("Invalid token on event", message);
                         handled = true;

                         l.unlock();
                         cv2.notify_one();
                     });


    handler.handle_event(event_str, {
            "T123",
            "xoxp-123",
            "U123",
            "xoxb-123",
            "B123",
    });

    std::unique_lock<std::mutex> l(m);
    cv1.wait(l, [&](){return !received;});
    ASSERT_FALSE(received);
    cv2.wait(l, [&](){return handled;});
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

    slack::http_event_client handler{"WHYYES", slack::http_event_client::parameter::thread_timeout{10ms}};

    bool received = false;
    bool handled = false;
    std::mutex m;
    std::condition_variable cv1;
    std::condition_variable cv2;

    handler.on<slack::event::message>([&](auto event, auto envelope)
                                      {
                                          std::unique_lock<std::mutex> l(m);

                                          received = true;

                                          l.unlock();
                                          cv1.notify_one();
                                      });
    handler.hears("More!", [&](auto message)
    {
        std::unique_lock<std::mutex> l(m);

        handled = true;

        l.unlock();
        cv2.notify_one();
    });


    handler.handle_event(event_str, {
            "T123",
            "xoxp-123",
            "U123",
            "xoxb-123",
            "B123",
    });

    std::unique_lock<std::mutex> l(m);
    cv1.wait(l, [&](){return received;});
    ASSERT_TRUE(received);
    cv2.wait(l, [&](){return handled;});
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

    slack::http_event_client handler{"WHYYES", slack::http_event_client::parameter::thread_timeout{10ms}};

    bool received = false;
    bool handled = false;
    std::mutex m;
    std::condition_variable cv1;
    std::condition_variable cv2;

    handler.on<slack::event::message_bot_message>([&](auto event, auto envelope)
                                                  {
                                                      std::unique_lock<std::mutex> l(m);

                                                      received = true;

                                                      l.unlock();
                                                      cv1.notify_one();
                                                  });
    handler.hears("More!", [&](auto message)
    {
        std::unique_lock<std::mutex> l(m);

        handled = true;

        l.unlock();
        cv2.notify_one();
    });


    handler.handle_event(event_str, {
            "T123",
            "xoxp-123",
            "U123",
            "xoxb-123",
            "B123",
    });

    std::unique_lock<std::mutex> l(m);
    cv1.wait(l, [&](){return received;});
    ASSERT_TRUE(received);
    cv2.wait(l, [&](){return handled;});
    ASSERT_TRUE(handled);
}