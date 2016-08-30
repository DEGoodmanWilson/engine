//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <string>
#include <functional>

namespace slack
{

enum class log_level
{
    FATAL = 0,
    ERROR,
    WARNING,
    INFO,
    DEBUG,
};


using logger_cb = std::function<void(log_level level, const std::string &message)>;

void set_logger(logger_cb logger);

void reset_logger();

} //namespace slack

std::string to_string(slack::log_level value);