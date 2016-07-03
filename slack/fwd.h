//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#define SLACK_FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)
