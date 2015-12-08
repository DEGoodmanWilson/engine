---
layout: default
title: Posting a message to Slack
---

# Posting a message to Slack

Posting a message to a Slack channel is one of the most common use cases. It couldn't be easier. You will need to know the Id of the channel you wish to post to, but in many cases this will be provided to you (see _e.g._ the section on responding to slash commands).

```
#include <slack/slack.h>

slack::channel_id channel = …;
auto response = slack::chat::post_message(channel, "some text");
```
There is no step three. 
