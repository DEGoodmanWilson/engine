//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <string>

namespace engine
{

// TYPES
using channel_id = std::string;

class error
{

};

namespace chat
{
namespace postMessage
{
using attachment = std::string;
}
} //namespace chat

} //namespace engine