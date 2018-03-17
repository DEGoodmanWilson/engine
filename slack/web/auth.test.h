//
// engine
//
// Copyright © 2017 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>


namespace slack { namespace auth
{

class test : public slack::base::response
{
public:
                
    
    template<class TOKEN>
    test(TOKEN &&token) : response{std::forward<TOKEN>(token)}
    {
        initialize_();
    }

    
    // parameters
    struct parameter
    {
    };

    // errors
    struct error : public slack::base::error
    {
    };

    // response
    std::string url;
    std::string teamname;
    std::string username;
    slack::team_id team_id;
    slack::user_id user_id;

    // parameter setters

private:
    void initialize_();


};

} } //namespace auth slack