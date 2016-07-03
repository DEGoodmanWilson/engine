//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <slack/types.h>
#include <slack/chat.h>

namespace engine
{

class slack
{
public:
    slack(const std::string & token);
    slack(std::string && token);

    ::engine::endpoints::chat chat;
};

} //namespace engine