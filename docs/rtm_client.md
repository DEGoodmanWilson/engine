---
layout: default
title: Using the Real-Time Messaging API
---


The Slack [Real-Time Messaging API](https://api.slack.com/rtm) is a mechanism for building chatbots that uses WebSockets—Slack provides a WebSocket URL to you, and once connected, Slack will send you a firehose of events over that connection. The RTM API has several distinct advantages over the Events API, depending on your use case:

- No need to run a webserver, or accept incoming connections, making it ideal for desktop or mobile apps.
- Very low latency, which makes for a more responsive bot.

On the other hand, it is very hard to scale with the RTM API, as you will need at least one persistent WebSocket connection per team you wish to connect to. If you are building a Slack App for distribution, we recommend using the [Events API](events_client.md) instead.

# IMPORTANT NOTE

At this time, the Engine `slack::rtm_event_client` API is unstable, and is not recommended for use. Once `slack::http_event_client` API is finalized, the RTM component will be re-written to match. In the meantime, we strongly recommend that you look at using the Events API instead. (Of course, if you are writing a custom integration, rather than an app, this is not an option for you, in which case, we invite your participation in finalizing this functionality!)