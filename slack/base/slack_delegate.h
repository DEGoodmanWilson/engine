//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

namespace slack
{

    class slack_delegate
    {
    public:
        virtual std::string token() const = 0;
    };

} //namespace slack