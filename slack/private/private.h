//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include "slack/base/response.h"
#include "slack/base/event.h"
#include <json/json.h>
#include <map>



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
    using factory_func = std::function<std::shared_ptr<T>(const Json::Value &)>;

    template<typename TDerived>
    void register_type(const std::string &name, factory_func constructor)
    {
        static_assert(std::is_base_of<T, TDerived>::value,
                      "factory::register_type doesn't accept this type because doesn't derive from base class");
        create_funcs_[name] = constructor;
    }

    std::shared_ptr<T> create(const std::string &name, const Json::Value &root)
    {
        if(create_funcs_.count(name))
        {
            auto it = create_funcs_.at(name);
            return it(root);
        }
        return nullptr;
    }

private:
    std::map<const std::string, factory_func> create_funcs_;
};

// TODO should this be static instead?
extern factory<slack::base::event> events_factory;

} //namespace slack_private