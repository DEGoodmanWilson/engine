//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/channel.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>

namespace slack { namespace channels
{

class create :
        public slack::base::response
{
public:
    //public interface
    create(const std::string& name);

    //parameters
    struct parameter
    {
        MAKE_BOOL_LIKE(exclude_archived);
    };

    //errors
    struct error : slack::base::error
    {
        static const std::string NAME_TAKEN;
        static const std::string RESTRICTED_ACTION;
        static const std::string NO_CHANNEL;
        static const std::string NOT_AUTHED;
        static const std::string INVALID_AUTH;
        static const std::string ACCOUNT_INACTIVE;
        static const std::string USER_IS_BOT;
        static const std::string USER_IS_RESTRICTED;
    };

    //response
    std::experimental::optional<slack::channel> channel;

    //parameter setters

private:
    void initialize_();

    std::string name_;
};

}} //namespace channels slack