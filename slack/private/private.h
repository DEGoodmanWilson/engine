//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include "config.h"
#include "base/response.h"
#include "base/event.h"
#include <json/json.h>
#include <map>

#define LOG(level, mesg) if (logger_) \
{ \
    logger_(level, mesg); \
}

#define LOG_FATAL(mesg) if (logger_) \
{ \
    logger_(log_level::FATAL, mesg); \
}

#define LOG_ERROR(mesg) if (logger_) \
{ \
    logger_(log_level::ERROR, mesg); \
}

#define LOG_INFO(mesg) if (logger_) \
{ \
    logger_(log_level::INFO, mesg); \
}

#define LOG_DEBUG(mesg) if (logger_) \
{ \
    logger_(log_level::DEBUG, mesg); \
}


namespace slack_private
{

Json::Value parse(const std::string &json);

Json::Value get(slack::base::response *obj,
                const std::string &endpoint,
                const slack::http::params &params,
                bool auth = true);

struct json_impl
{
    json_impl(const Json::Value &json) : json{json}
    { }

    Json::Value json;
};


template<typename T>
class factory
{
public:
    using factory_func = std::function<std::shared_ptr<T>(const slack::team_id &, const Json::Value &)>;

    template<typename TDerived>
    void register_type(const std::string &name, factory_func constructor)
    {
        static_assert(std::is_base_of<T, TDerived>::value,
                      "factory::register_type doesn't accept this type because doesn't derive from base class");
        create_funcs_[name] = constructor;
    }

    std::shared_ptr<T> create(const std::string &name, const slack::team_id &team_id, const Json::Value &root)
    {
        if(create_funcs_.count(name))
        {
            auto it = create_funcs_.at(name);
            return it(team_id, root);
        }
        return nullptr;
    }

private:
    std::map<const std::string, factory_func> create_funcs_;
};

// TODO should this be static instead?
extern factory<slack::base::event> events_factory;

} //namespace slack_private