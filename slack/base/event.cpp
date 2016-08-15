//
// Created by D.E. Goodman-Wilson on 8/15/16.
//

#include "base/event.h"
#include <json/json.h>

namespace slack { namespace base
{

template<>
event::event(const Json::Value &parsed_json)
{
    if (parsed_json.isNull()) return;
    if (parsed_json["token"].isString()) token = parsed_json["token"].asString();
};

}} //namespace base slack