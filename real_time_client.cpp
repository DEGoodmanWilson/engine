//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/real_time_client.h"
#include <thread>

namespace slack
{

// This method will block until the connection is complete
real_time_client::real_time_client(const std::string &url)
        : wss_client_{url, false}, is_connected_{false}
{
    wss_client_.onopen = std::bind(&real_time_client::on_open_, this);
    wss_client_.onclose = std::bind(&real_time_client::on_close_, this, std::placeholders::_1, std::placeholders::_2);
//    wss_client_.onmessage=[&client](shared_ptr<WssClient::Message> message) {
//        auto message_str=message->string();
//
//        cout << "Client: Message received: \"" << message_str << "\"" << endl;
//
//        cout << "Client: Sending close connection" << endl;
//        wss_client_.send_close(1000);
//    };
//
//    wss_client_.onopen=[&client]() {
//        cout << "Client: Opened connection" << endl;
//
//        string message="Hello";
//        cout << "Client: Sending message: \"" << message << "\"" << endl;
//
//        auto send_stream=make_shared<WssClient::SendStream>();
//        *send_stream << message;
//        wss_client_.send(send_stream);
//    };
//
//    wss_client_.onclose=[](int status, const string& reason) {
//        cout << "Client: Closed connection with status code " << status << endl;
//    };
//
//    //See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
//    wss_client_.onerror=[](const boost::system::error_code& ec) {
//        cout << "Client: Error: " << ec << ", error message: " << ec.message() << endl;
//    };

}


bool real_time_client::start()
{
    wss_client_.start();
    return true;
}


bool real_time_client::stop()
{
    wss_client_.stop();
    return true;
}


void real_time_client::on_open_()
{
    is_connected_ = true; //it's atomic, so this is ok!
}


void real_time_client::on_close_(int status, const std::string& reason)
{
    is_connected_ = false;
    //TODO other things.
}

} //namespace slack