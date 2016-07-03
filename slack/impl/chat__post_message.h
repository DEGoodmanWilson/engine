//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <slack/types.h>

namespace engine
{
class chat__post_message_
{
public:
    void set_option(const chat::postMessage::attachment &attachment)
    { }

    void set_option(chat::postMessage::attachment &&attachment)
    { }

    int execute()
    { return 5; }
};
} //namespace engine