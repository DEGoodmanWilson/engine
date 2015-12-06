---
layout: default
title: Engine
---

# A C++ library for building Slack-enabled applications

You want to connect your app or game with Slack. Or you want to write a Slack bot. And you want to do it in C++, because C++ is _awesome_. You need a Rocket Engine.

## Prerequisites

A C++11 compiler. Some kind of HTTP client library (we like [CPR](https://github.com/whoshuu/cpr)). And of course an idea.

# Installation & Usage

# Using Engine

## Setting up Slack, and getting a token

## Initializing the library

You'll need to do two things to get the library ready to go:

1) Give the library a valid Slack token

2) Hook up your GET and POST methods

Here's a snippet showing how to do both of these things. In this example, we suppose you are using [CPR](https://github.com/whoshuu/cpr) for making HTTP requests, but you can use whatever library you prefer.

```
slack::set_token("xoxp-1234-5678"); //get this from Slack, see above

slack::http::get = [](std::string url, slack::http::params params) -> slack::http::response {
    cpr::Parameters p;
    for (auto &kv : params)
    {
        p.AddParameter({kv.first, kv.second});
    }

    auto response = cpr::Get(cpr::Url{url}, p);
    return {static_cast<uint32_t>(response.status_code), response.text};
};

slack::http::post = [](std::string url, slack::http::params params) -> slack::http::response {
    cpr::Payload p;
    for (auto &kv : params)
    {
        p.AddParameter({kv.first, kv.second});
    }

    auto response = cpr::Post(cpr::Url{url}, p);
    return {static_cast<uint32_t>(response.status_code), response.text};
};
```

## Posting a message to a channel

# End Matter

## Disclaimer

This library has only begun, and is a contant state of flux.