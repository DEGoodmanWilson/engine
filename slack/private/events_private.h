//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <json/json.h>
#include "event/hello.h"
#include "event/user_typing.h"
#include "event/pong.h"
#include "event/channel_archive.h"
#include "event/message.h"
#include "event/message_bot_message.h"
#include "event/message_channel_archive.h"
#include "event/message_channel_join.h"
#include "event/unknown.h"

namespace slack { namespace event
{

void initialize_events(void);

}} //namespace event slack