//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>

namespace slack { namespace channels
{

class archive :
        public slack::base::response
{
public:
    //public interface
    archive(const channel_id &channel);

    //parameters
    struct parameter
    {
    };

    //errors
    struct error :
            public slack::base::error
    {
        static const std::string CHANNEL_NOT_FOUND;
        static const std::string ALREADY_ARCHIVED;
        static const std::string CANT_ARCHIVE_GENERAL;
        static const std::string LAST_RA_CHANNEL;
        static const std::string RESTRICTED_ACTION;
        static const std::string NOT_AUTHED;
        static const std::string INVALID_AUTH;
        static const std::string ACCOUNT_INACTIVE;
        static const std::string USER_IS_BOT;
        static const std::string USER_IS_RESTRICTED;
    };

    //response

    //parameter setters

private:
    void initialize_();

    channel_id channel_;
};

} } //namespace channels slack