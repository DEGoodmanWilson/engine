//
// Created by D.E. Goodman-Wilson on 8/30/16.
//

#include "config.h"

namespace slack
{

logger_cb logger_ = nullptr;

void set_logger(logger_cb logger)
{
    logger_ = logger;
}

void reset_logger()
{
    logger_ = nullptr;
}

} //namespace slack


std::string to_string(slack::log_level value)
{
    switch(value)
    {
        case slack::log_level::FATAL:
            return "FATAL";
        case slack::log_level::ERROR:
            return "ERROR";
        case slack::log_level::WARNING:
            return "WARNING";
        case slack::log_level::INFO:
            return "INFO";
        case slack::log_level::DEBUG:
        default:
            return "DEBUG";
    }
}