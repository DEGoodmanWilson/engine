//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/macros.h>
#include <string>


namespace slack
{

using team_id = std::string; //for now
using user_id = std::string; //for now
namespace auth
{

struct response //: ::slack:response
{
    response() : ok{false}
    { }

    response(bool ok,
             const std::string &url,
             const std::string &team,
             const std::string &user,
             const slack::team_id &team_id,
             const slack::user_id &user_id) :
            ok{ok}, url{url}, team{team}, user{user}, team_id{team_id}, user_id{user_id}
    { }

    bool ok;
    std::string url;
    std::string team;
    std::string user;
    ::slack::team_id team_id;
    ::slack::user_id user_id;
};

class test_wrapper
{
public:
    test_wrapper() = default;

    response get_response();

private:

};

response test();


} //namespace auth
} //namespace slack