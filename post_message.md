---
layout: default
title: Posting a message to Slack
---

# Posting a message to Slack

Posting a message to a Slack channel is one of the most common use cases. It couldn't be easier. You will need to know the Id of the channel you wish to post to, but in many cases this will be provided to you (see _e.g._ the section on responding to slash commands).

    #include <slack/slack.h>
    
    slack::channel_id channel = …;
    auto response = slack::chat::post_message(channel, "some text");

There is no step three. 

## Error handling

Of course you want to make sure your message was successfully posted! You need only check that the returned object evaluates to `true`, and if not, then examine the `error` property on the response:

    if (!response)
    {
        std::cout << response.error << std::endl;
        if (response.error == slack::chat::response::error::post_message::CHANNEL_NOT_FOUND)
        {
            //we were lied to about the channel id!
        }
    }

(Yes, that's quite the nested namespace! We can clean that up with a `using namespace slack::chat` directive of course!)

## Additional options

Of course, the Slack API allows a number of different options, and we can pass those easily!

    auto response = slack::chat::post_message(channel, "Hello, world",
        slack::chat::parameter::post_message::icon_url{"http://iosicongallery.com/iosicongallery/img/512/slack-2014.png"},
        slack::chat::parameter::post_message::as_user{true}
    );

The optional parameters may be specified in any order, in any combination.