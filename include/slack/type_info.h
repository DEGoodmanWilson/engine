//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <typeinfo>

/***
 * A helper class that encapsulates type_info in a helpful way. I bet this can be eliminated.
 * Adapted from http://www.gamedev.net/page/resources/_/technical/game-programming/effective-event-handling-in-c-r2459
 */

namespace slack
{

class type_info
{
public:
	explicit type_info(const std::type_info &info) : type_info_(info)
	{ };

	bool operator<(const type_info &rhs) const
	{
		return type_info_.before(rhs.type_info_) != 0;
	}

private:
	const std::type_info &type_info_;
};

} //namespace