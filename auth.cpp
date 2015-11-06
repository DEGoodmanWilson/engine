//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "auth.h"

namespace slack
{

std::string auth::test()
{
    //TODO make this more robust!
    return get_("auth.test").body();
}

} //namespace slack