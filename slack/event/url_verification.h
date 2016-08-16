//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/base/event.h>
#include <slack/optional.hpp>


namespace slack { namespace event
{


struct url_verification :
        public base::event
{
    static const std::string type;


    url_verification() = default;
    ~url_verification() = default;

    template<class json>
    url_verification(const json &parsed_json);

    std::string challenge;
};


}} //namespace event slack