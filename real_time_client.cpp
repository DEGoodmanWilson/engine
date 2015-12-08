//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/real_time_client.h"
#include <slack/rtm.start.h>
#include <easywsclient/easywsclient.hpp>
#include <thread>

namespace slack
{

using client = websocketpp::client<websocketpp::config::asio_client>;

// This method will block until the connection is complete
real_time_client::real_time_client(const std::string &url)
        : open_{false},done_{false},url_{url}
{
    // set up access channels to only log interesting things
    client_.clear_access_channels(websocketpp::log::alevel::all);
    client_.set_access_channels(websocketpp::log::alevel::connect);
    client_.set_access_channels(websocketpp::log::alevel::disconnect);
    client_.set_access_channels(websocketpp::log::alevel::app);

    // Initialize the Asio transport policy
    client_.init_asio();

    // Bind the handlers we are using
    using websocketpp::lib::placeholders::_1;
    using websocketpp::lib::bind;
    client_.set_open_handler(bind(&telemetry_client::on_open, this, _1));
    client_.set_close_handler(bind(&telemetry_client::on_close, this, _1));
    client_.set_fail_handler(bind(&telemetry_client::on_fail, this, _1));


}

real_time_client::~real_time_client()
{
    if(asio_thread_.joinable())
        asio_thread_.join();
    else
        asio_thread_.detach();

    if(telemetry_thread_.joinable())
        telemetry_thread_.join();
    else
        telemetry_thread_.detach();
}

bool real_time_client::run();
    // Create a new connection to the given URI
    websocketpp::lib::error_code ec;
    client::connection_ptr con = client_.get_connection(url_, ec);
    if (ec)
    {
        client_.get_alog().write(websocketpp::log::alevel::app,
                                  "Get Connection Error: " + ec.message());
        return false;
    }

    // Grab a handle for this connection so we can talk to it in a thread
    // safe manor after the event loop starts.
    hdl_= con->get_handle();

    // Queue the connection. No DNS queries or network connections will be
    // made until the io_service event loop is run.
    client_.connect(con);

    // Create a thread to run the ASIO io_service event loop
    asio_thread_ = {&client::run, &client_};

    // Create a thread to run the telemetry loop
    telemetry_thread_ = {&telemetry_client::telemetry_loop, this};

    return true;
}

} //namespace slack

} //namespace slack