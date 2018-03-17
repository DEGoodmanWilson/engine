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


namespace slack { namespace api
{

class test : public slack::base::response
{
public:
                
    
    template<typename ...Os>
    test()
    {
        initialize_();
    }

    template<typename ...Os>
    test(Os &&...os)
    {
        slack::set_option<test>(*this, std::forward<Os>(os)...);
        initialize_();
    }

    
    // parameters
    struct parameter
    {
        SLACK_MAKE_STRING_LIKE(error);       //"" is an unknown type
        SLACK_MAKE_STRING_LIKE(foo);       //"" is an unknown type
    };

    // errors
    struct error : public slack::base::error
    {
    };

    // response
    std::map<std::string, std::string> args;

    // parameter setters
    void set_option(const parameter::error &error)
    { error_ = error; }

    void set_option(parameter::error &&error)
    { error_ = std::move(error); }

    void set_option(const parameter::foo &foo)
    { foo_ = foo; }

    void set_option(parameter::foo &&foo)
    { foo_ = std::move(foo); }


private:
    void initialize_();


    std::experimental::optional<parameter::error> error_;
    std::experimental::optional<parameter::foo> foo_;
};

} } //namespace api slack