---
layout: default
title: Engine
---

[![Build Status](https://travis-ci.org/DEGoodmanWilson/engine.svg)](https://travis-ci.org/DEGoodmanWilson/engine)
[![Coverage Status](https://codecov.io/gh/DEGoodmanWilson/engine/branch/master/graph/badge.svg)](https://codecov.io/gh/DEGoodmanWilson/engine)
[![badge](https://img.shields.io/badge/conan.io-engine%2F{{ site.version }}-green.svg?logo=data:image/png;base64%2CiVBORw0KGgoAAAANSUhEUgAAAA4AAAAOCAMAAAAolt3jAAAA1VBMVEUAAABhlctjlstkl8tlmMtlmMxlmcxmmcxnmsxpnMxpnM1qnc1sn85voM91oM11oc1xotB2oc56pNF6pNJ2ptJ8ptJ8ptN9ptN8p9N5qNJ9p9N9p9R8qtOBqdSAqtOAqtR%2BrNSCrNJ/rdWDrNWCsNWCsNaJs9eLs9iRvNuVvdyVv9yXwd2Zwt6axN6dxt%2Bfx%2BChyeGiyuGjyuCjyuGly%2BGlzOKmzOGozuKoz%2BKqz%2BOq0OOv1OWw1OWw1eWx1eWy1uay1%2Baz1%2Baz1%2Bez2Oe02Oe12ee22ujUGwH3AAAAAXRSTlMAQObYZgAAAAFiS0dEAIgFHUgAAAAJcEhZcwAACxMAAAsTAQCanBgAAAAHdElNRQfgBQkREyOxFIh/AAAAiklEQVQI12NgAAMbOwY4sLZ2NtQ1coVKWNvoc/Eq8XDr2wB5Ig62ekza9vaOqpK2TpoMzOxaFtwqZua2Bm4makIM7OzMAjoaCqYuxooSUqJALjs7o4yVpbowvzSUy87KqSwmxQfnsrPISyFzWeWAXCkpMaBVIC4bmCsOdgiUKwh3JojLgAQ4ZCE0AMm2D29tZwe6AAAAAElFTkSuQmCC)](http://www.conan.io/source/engine/{{ site.version }}/DEGoodmanWilson/stable)

Connect your desktop app, backend, or game to Slack. Engine provides a statically typed, reliable, and simple to use C++ interface to Slack’s Web, Real Time, and Events APIs using modern, idiomatic C++.

## Prerequisites

A C++14 capable compiler (tested against gcc 4.9, clang 3.6), CMake 2.8. [Conan](https://www.conan.io) for installing dependencies.

## Example code

Here is a quick example that you can run to post a message into `#general` on your Slack team. You'll need a [testing token](https://api.web_client.com/docs/oauth-test-tokens), which you should pass as an environment variable called `SLACK_TOKEN`.

```cpp
#include <iostream>
#include <slack/slack.h>

int main()
{
    slack::web web_client{std::getenv("SLACK_TOKEN")};
    auto response = web_client.chat.postMessage("#general", "Hello, world!");

    std::cout << response.message->text << std::endl;

    return 0;
}
```

## License

[MIT](https://github.com/DEGoodmanWilson/engine/blob/master/LICENSE)

## Disclaimer

This library has only begun, and there is yet a lot that is missing. It's still usable, but you might not find everything is as you would like it.