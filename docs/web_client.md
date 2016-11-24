---
layout: default
title: Calling the Slack Web API
---

The Slack [Web API](https://api.slack.com/web) is a straightforward remote procedure call style API encapsulated by the `slack::web_client` class. The `slack::web_client` constructor takes an optional string containing a Slack access token. Most of the Web API requres a token, although there are a few exceptions. See [Connecting your project to Slack](setup.html) to learn more about acquiring an access token.

What follows are a number of use cases, illustrating how to use `slack::web_client` to achieve your aims

# Posting a message

```cpp
#include <iostream>
#include <slack/slack.h>

int main()
{
    // Here and elsewhere, we assume that the token in an environment variable
    // Notice that this assumption might not really be accurate if you are running a Slack App
    slack::web_client web_client{std::getenv("SLACK_TOKEN")};
    
    // You can post by channel name, or by channel ID (if you have it)
    auto response = web_client.chat.postMessage("#general", "Hello, world!");
}
```

## Posting a message with attachments

There are quite a number of options to the `chat.postMessage()` method, all of which are supported here. For example, Slack offers the option to [format messages with "attachments"](https://api.slack.com/docs/message-attachments), which are like cards that attach to the bottom of a message. Adding attachments to your own messages is simple

```cpp
#include <iostream>
#include <slack/slack.h>

int main()
{
    slack::web_client web_client{std::getenv("SLACK_TOKEN")};

    // You can post by channel name, or by channel ID (if you have it)
    auto response = web_client.chat.postMessage("#general", "Hello, world!",
        slack::chat::postMessage::parameter::attachments{
            {
                slack::attachment::parameter::title{"This is an attachment"},
                slack::attachment::parameter::text{"This is the attachment text"},
                slack::attachment::parameter::color{"#FF0000"}
            },
            {
                slack::attachment::parameter::title{"This is another attachment"},
                slack::attachment::parameter::text{"This is the attachment text"},
                slack::attachment::parameter::color{"#0000FF"}
            },
        }
    );
}
```

# Updating the content of a message

Bots can update the contents of messages that they post. You'll need to have the original message's `ts` (timestamp) and `channel` properties to uniquely identify the message to be updated.

```cpp
#include <iostream>
#include <slack/slack.h>

int main()
{
    slack::web_client web_client{std::getenv("SLACK_TOKEN")};

    slack::ts my_ts{"123.456"};
    slack::channel_id my_channel_id{"C123"};

    auto response = web_client.chat.update(my_ts, my_channel_id, "Replacement message");
}
```

As with `chat.postMessage`, you can include attachments and other formatting options in the updated message.

# Deleting a message

You can also delete messages that you have posted. As with `chat.update`, you need to know the message's timestamp and channel.

```cpp
#include <iostream>
#include <slack/slack.h>

int main()
{
    slack::web_client web_client{std::getenv("SLACK_TOKEN")};

    slack::ts my_ts{"123.456"};
    slack::channel_id my_channel_id{"C123"};

    auto response = web_client.chat.delete_it(my_ts, my_channel_id);
}
```

# Getting a information on a team's channels

Sometimes, you'll want to query Slack to learn something. For example, perhaps you'd like to get a list of the available channels in a team. The Slack Web API responses are statically typed, so you don't have to guess at the structure.

When Slack returns an array of objects, Engine uses `std::vector` to represent that array.

```cpp
#include <iostream>
#include <slack/slack.h>

int main()
{
    slack::web_client web_client{std::getenv("SLACK_TOKEN")};

    auto response = web_client.channels.list();

    // First we test if the response is not an error response
    if(response)
    {
        for(const auto &channel : response.channels)
        {
            std::cout << channel.name << " " << channel.id << " " << channel.topic.value << std::endl;
            for (const auto &member : channel.members)
            {
                std::cout << "   " << member << std::endl;
            }
        }
    }
}
```

# General Web API patterns

In general, the methods and parameters exposed by Engine's `slack::web_client` match those in the [Web API](https://api.slack.com/methods) (with the notable exception of any Slack endpoint named `delete`—these have been renamed to `delete_it` in Engine because, of course, `delete` is a reserved keyword in C++).

At the moment, Engine only supports a limited subset of the Slack Web API. More methods are being added as time goes on, however the process is slow, tedious, and inconsistent as there is no good way (yet!) to automate it.

## Calling convention

Required parameters appear in the same order in Engine as they do in the Slack documentation. Optional parameters are passed using the named parameter pattern—you name the parameter you wish to provide, and can provide them in any order you like after the required parameters.

The exception is the `token` parameter required by nearly all Slack Web API endpoints. This parameter is filled in automatically for you when it is required, and you need not provide it yourself.

For example, consider [`chat.postMessage` (link)](https://api.slack.com/methods/chat.postMessage) which has a large number of required and optional parameters. This method, of course, posts a message into a channel, and requires, first, a channel ID to post a message into, and the text of the message itself.

```cpp
    web_client.chat.postMessage("C1234", "this is my message");
```

If you want to pass optional parameters, these come after the required parameters. Let's suppose we want to pass `as_user` as `false` and `usename` as `AwesomeBot`. We can do it like this:

```cpp
    web_client.chat.postMessage("C1234", "this is my message",
        slack::chat::postMessage::parameter::as_user{true},
        slack::chat::postMessage::parameter::username{"AwesomeBot"}
    );
```

But the order doesn't matter for optional parameters, so we could do it like this too:

```cpp
    web_client.chat.postMessage("C1234", "this is my message",
        slack::chat::postMessage::parameter::username{"AwesomeBot"},
        slack::chat::postMessage::parameter::as_user{true}
    );
```


## Return values

The Slack API _always_ returns an object with an "ok" field, indicating whether the call succeeded or not. You can test whether the response is an "ok" response by treating the response as a bool.

### Success

On success, the `response` object will evaluate to `true`, and the `response` object will have all of the fields as indicated by the API documentation for the method you are calling. For example, when calling `chat.postMessage()`, you can anticipate that the return object will have `ts`, `channel`, and `message` fields. However, sometimes the fields will be of type `std::experimental::optional`, as the Slack API is often inconsistent about the structure of the objects it returns, and is in a constant state of flux—be sure to check for the existence of a field before using it to avoid heartache later, and of course to access the contents you wil need to dereference the field.

At the moment, which fields are `optional` is not fully standardized, and it can be hard to discover when coding. A future version of Engine will address this unfortunate issue in a more principled way.

```cpp
    auto response = web_client.chat.postMessage(...);
    
    if(response.ts && response.channel && response.message)
    {
        std::cout << *response.ts << " " << *response.channel << " " << response.message->test << std::endl;
    }
```

### Error

On error, Slack will provide an `error` object that contains a string with the error code. You can look the error code up on the Slack API web page for the method you are calling. For example, `chat.postMessage` will return `channel_not_found` if you attempt to post a message into a non-existant channel.

In Engine, the response object will evaluate to `false` in the case there is an error, either because the call failed with a non-success HTTP error code, or because Slack responded with an error object. All response objects contain the `error_message` field. This field will be populated with the Slack error code returned, if the response is a Slack error object.

```cpp
#include <iostream>
#include <slack/slack.h>

int main()
{
    slack::web_client web_client{std::getenv("SLACK_TOKEN")};

    // `ABC` is an invalid channel ID, so will surely fail
    auto response = web_client.chat.postMessage("ABC", "oh no!");
    if(!response) // check if there was an error. It's basically guaranteed
    {
        std::cout << response.error_message << std::endl;
        // or we can compare it to an enum containing all possible error messages for this method
        std::cout << (response.error_message == slack::chat::postMessage::error::CHANNEL_NOT_FOUND) << std::endl;
    }
}
```

In the case that there was an HTTP transport error, `error_message` will contain the HTTP error code encountered.

```cpp
#include <iostream>
#include <slack/slack.h>

int main()
{
    slack::web_client web_client{std::getenv("SLACK_TOKEN")};

    web_client.set_uri("http://google.com/"); // Never do this

    auto response = web_client.chat.postMessage("ABC", "oh no!");
    if(!response) // check if there was an error. It's basically guaranteed
    {
        // Will output "404"
        std::cout << response.error_message << std::endl;
    }
}
```