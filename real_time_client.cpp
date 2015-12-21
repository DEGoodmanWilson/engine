//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/real_time_client.h"
#include "private.h"
#include <thread>
#include <json/json.h>

namespace slack
{

namespace event
{
void initialize_events(void); //declared in event.cpp
}

void real_time_client::initialize_(void)
{
    event::initialize_events();
}

// This method will block until the connection is complete
real_time_client::real_time_client(const std::string &url)
        : wss_client_{std::string{url}.erase(0,6), false}, is_connected_{false}
{
    wss_client_.onopen = std::bind(&real_time_client::on_open_, this);
    wss_client_.onclose = std::bind(&real_time_client::on_close_, this, std::placeholders::_1, std::placeholders::_2);
    wss_client_.onerror = std::bind(&real_time_client::on_error_, this, std::placeholders::_1);
    wss_client_.onmessage = std::bind(&real_time_client::on_message_, this, std::placeholders::_1);

    initialize_();
}


void real_time_client::start()
{
    wss_client_.start();
}


void real_time_client::stop()
{
    wss_client_.stop();
}


void real_time_client::on_open_()
{
    is_connected_ = true; //it's atomic, so this is ok!
    // And start the ping thread
}


void real_time_client::on_close_(int status, const std::string& reason)
{
    is_connected_ = false;
    //TODO other things.
    // and stop the ping thread
}


void real_time_client::on_error_(const boost::system::error_code &error_code)
{
    //TODO
    std::cout << error_code << std::endl;
}


void real_time_client::on_message_(std::shared_ptr<WssClient::Message> mesg)
{
    handle_event_from_slack(mesg->string());
}

void real_time_client::handle_event_from_slack(const std::string &event_str)
{
    //TODO this is where the rubber meets the road
    std::cout << event_str << std::endl;

    Json::Value result_ob;
    Json::Reader reader;
    bool parsed_success = reader.parse(event_str, result_ob, false);
    if (!parsed_success)
    {
        //TODO
        return;
    }

    std::string type = result_ob["type"].asString();
    auto event = slack_private::events_factory.create(type, result_ob);

    handle_event(event);
}

bool real_time_client::post_event_to_slack(std::shared_ptr<base::event> event)
{
    //TODO
    return false;
}
} //namespace slack