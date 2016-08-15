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
    std::string name = "";

    handler.register_event_handler<slack::event::unknown>([&](std::shared_ptr<slack::event::unknown> event) {
            EXPECT_TRUE(static_cast<bool>(event));
            received = true;
            name = event->name;
        });

    handler.handle_event(event_str);

    ASSERT_TRUE(received);
    ASSERT_EQ("WATWAT", name);
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

//
//
//TEST(event_handler, user_typing
//{
//    std::string event_str = R"(
//    {
//        "type": "user_typing",
//        "channel": "C02ELGNBH",
//        "user": "U024BE7LH"
//    }
//    )";
//
//    auto socket = std::make_shared<websocket>();
//
//    slack::real_time_client client{slack::real_time_client::parameter::url{"none"}, socket};
//    client.register_event_handler<slack::event::user_typing>([](std::shared_ptr<slack::event::user_typing> event) {
//        ASSERT_TRUE(static_cast<bool>(event));
//        ASSERT_EQ("C02ELGNBH", event->channel);
//        ASSERT_EQ("U024BE7LH", event->user);
//    });
//    socket->receive_message(event_str);
//}
//
//TEST(event_handler, non_existant)
//{
//    std::string event_str = R"(
//    {
//        "type": "foobar"
//    }
//    )";
//
//    auto socket = std::make_shared<websocket>();
//
//    slack::real_time_client client{slack::real_time_client::parameter::url{"none"}, socket};
//
//    ASSERT_NO_FATAL_FAILURE(socket->receive_message(event_str));
//}
//
//class websocket_ping_mock :
//        public slack::websocket
//{
//
//public:
//    websocket_ping_mock() : ping_count{0}
//    { }
//
//    void receive_message(const std::string &message)
//    {
//        this->on_message(message);
//    }
//
//
//    virtual void start(const std::string &url) override
//    {
//        on_connect();
//    }
//
//    virtual void stop() override
//    {
//    }
//
//    virtual void send_message(const std::string &message) override
//    {
//        //check to see if a ping gets sent
//        if (message.find("ping") != std::string::npos)
//        {
//            ++ping_count;
////            std::cout << "ping count incr " << ping_count << std::endl;
//        }
//    }
//
//    int ping_count;
//};
//
//TEST(event_handler, test_no_final_ping)
//{
//    auto socket = std::make_shared<websocket_ping_mock>();
//
//    slack::real_time_client client{slack::real_time_client::parameter::url{"none"}, socket,
//                                   slack::real_time_client::parameter::ping_interval{100}};
//
//    client.start();
//    //TODO need to do this better
//    while (socket->ping_count <= 1);
//
//    client.stop();
//
//    ASSERT_EQ(2, socket->ping_count); //Because we send a ping first thing, and then one after n milliseconds
//}
//
//TEST(event_handler, actually_connect_sync)
//{
//    slack::real_time_client client{};
//    bool done = false;
//
//    //Set up a handler to handle that first hello. Notice that we, uh, really ought to time out in case we don't connect!
//    client.register_event_handler<slack::event::hello>([&](std::shared_ptr<slack::event::hello> event) {
//        ASSERT_TRUE(static_cast<bool>(event));
//        done = true;
//        client.stop();
//    });
//
//    client.start();
//
//    ASSERT_TRUE(done);
//}
//
//TEST(event_handler, test_ping)
//{
//    slack::real_time_client client{};
//    bool done = false;
//
//    //Set up a handler to handle that first hello. Notice that we, uh, really ought to time out in case we don't connect!
//    client.register_event_handler<slack::event::pong>([&](std::shared_ptr<slack::event::pong> event) {
//        ASSERT_TRUE(static_cast<bool>(event));
//        done = true;
//        client.stop();
//    });
//
//    client.start();
//
//    ASSERT_TRUE(done);
//}
//
//TEST(event_handler, test_failed_socket_connection)
//{
//    slack::real_time_client client{
//            slack::real_time_client::parameter::url{"wss://foobar.example"}}; //this should just fail spectacularly
//
//    bool error = false;
//    bool connect = false;
//
//    client.on_connect = [&]() {
//        //This shouldn't happen!
//        connect = true;
//        client.stop();
//    };
//    client.on_error = [&](websocket::error_code code, bool will_reconnect) {
//        //This _should_ happen
//        error = true;
//        client.stop();
//    };
//
//    client.start();
//
//    ASSERT_TRUE(error);
//    ASSERT_FALSE(connect);
//}
//
//TEST(event_handler, test_failed_socket_connection_with_reconnect)
//{
//    slack::real_time_client::parameter::reconnect_policy policy{2, std::chrono::milliseconds{50}, 1.0};
//
//    slack::real_time_client client{slack::real_time_client::parameter::url{"wss://foobar.example"},
//                                   policy}; //this should just fail spectacularly
//
//    bool error = false;
//    int reconnect_count = 0;
//
//    client.on_connect = [&]() {
//        //This shouldn't happen!
//        client.stop();
//    };
//    client.on_error = [&](slack::websocket::error_code code, bool will_reconnect) {
//        //This _should_ happen
//        if (will_reconnect)
//        {
//            ++reconnect_count;
//        }
//        error = true;
//        ASSERT_GE(2, reconnect_count);
//    };
//
//    client.start();
//
//    ASSERT_TRUE(error);
//}
//
//TEST(event_handler, test_failed_socket_connection_with_reconnect_timing)
//{
//    slack::real_time_client::parameter::reconnect_policy policy{2, std::chrono::milliseconds{50}, 2.0};
//
//    slack::real_time_client client{slack::real_time_client::parameter::url{"wss://foobar.example"},
//                                   policy}; //this should just fail spectacularly
//
//
//    bool error = false;
//    int reconnect_count = 0;
//    auto retry_duration = policy.retry_interval;
//
//    auto start_time = std::chrono::steady_clock::now();
//    auto delta = std::chrono::milliseconds{10};
//
//    client.on_connect = [&]() {
//        //This shouldn't happen!
//        client.stop();
//    };
//    client.on_error = [&](slack::websocket::error_code code, bool will_reconnect) {
//        //This _should_ happen
//
//        if (reconnect_count) //ignore first attempt --- we only care about _re_connects
//        {
//
//            auto end_time = std::chrono::steady_clock::now();
//            auto diff = end_time - start_time;
//            auto max = retry_duration + delta;
//            auto min = retry_duration - delta;
////        std::cout << "retry_duration " << std::chrono::duration<double, std::milli>(retry_duration).count() << " ms" <<
////        std::endl;
////        std::cout << "delta " << std::chrono::duration<double, std::milli>(delta).count() << " ms" << std::endl;
////
////        std::cout << std::chrono::duration<double, std::milli>(min).count() << " ms" << std::endl;
////        std::cout << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
////        std::cout << std::chrono::duration<double, std::milli>(max).count() << " ms" << std::endl;
//
//            ASSERT_LE(min, diff);
//            ASSERT_GE(max, diff);
//            retry_duration *= policy.retry_backoff_factor;
//            delta *= policy.retry_backoff_factor;
//        }
//        start_time = std::chrono::steady_clock::now();
//
//        error = true;
//        if (will_reconnect)
//        {
//            ++reconnect_count;
//        }
//        ASSERT_GE(2, reconnect_count);
//
//    };
//
//    client.start();
//
//    ASSERT_TRUE(error);
//}