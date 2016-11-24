---
layout: default
title: Using the Events API
---

The Slack [Events API](https://api.slack.com/events-api) is a mechanism for building chatbots that uses HTTP—you provide a webhook to Slack, and Slack will notify you of new events on that webhook. The Events API has several distinct advantages over the Real-Time Messaging API, depending on your use case:

- Easier to scale, in case you are building an app that will connect to thousands of teams
- Slack can filter which events you receive for you, reducing your server load when you are interested in only a subset of the total available events.

On the other hand, the Events API does require that your bot is able to accept incoming connections, which means it is not generally suitable for desktop or mobile apps. Moreover, the overhead of HTTP connections means that there is much higher latency, but in most cases this won't be noticed by your human users. Finally, at this time, the Events API is only available to Slack Apps—if you are building a custom integration for only your team, you _must_ use the [RTM API](rtm_client.md) instead.

Please note that at this time, Engine's support for the Events API is under heavy development, and the API is subject to significant change while Engine is in beta.

# Getting ready to use the Events API

Please read carefully the [official documentation](https://api.slack.com/events-api) for the Events API to learn how to prepare your app to receive events!

Once you have done that, you'll need to do two things with your project. The first is to set up an embedded HTTP server such as [Luna](https://don.goodman-wilson.com/luna) to receive the events from Slack. The second is to create an instance of `slack::http_event_client`.
 
## Setting up a webserver

Your code will need to be able to handle incoming HTTP requests, in some fashion or other. Slack will send to your HTTP endpoint a JSON-encoded object that should be passed directly to Engine (more about this below). Whatever library you use to handling HTTP requests (naturally, we like [Luna](https://don.goodman-wilson.com/luna)), you will need to do some handling._

Whenever an event you have subscribed to occurs on any of the teams your app is installed on, Slack will call your HTTP endpoint. The body of this request will contain a JSON encoded object that you should pass directly to Engine without modification (more on how to do this below).

In addition to this JSON object, Engine will require the access tokens associated with the team that generated this event. The event may, of course, have originated from any team that your app is installed on. When your app is installed using [OAuth2](https://api.slack.com/docs/oauth), you will have recieved an object containing one or more access tokens, as well as information on the user who installed your app. You should persist that data somewhere (securely!), and pass it in a `slack::token` object to Engine whenever you receive an event (more on how to do this below).

Finally, one last consideration is that when you are first setting up your app to receive events over the Events API, Slack demands that it verify that you have a working HTTP endpoint. So it is necessary that your app be running somewhere that Slack can see it (using, perhaps, [ngrok](https://api.slack.com/tutorials/tunneling-with-ngrok)). Moreover, the payload that Slack sends in this case is somewhat different. Specically, Slack will pass an JSON object as a query parameter named `event` to your endpoint—all you need to do is to pass that JSON object directly to Engine. 

## Using `slack::http_event_client`

The `slack::http_event_client` class handles receiving, parsing, and emitting Slack events. It uses background threads to ensure responsiveness. You will need to construct one (just one will do) such object; it must be initialized with the verification token that Slack provides you when you set up your Slack App. This verification token will remain the same regardless of where the events Slack send originate from.

The core of `slack::http_event_client` is the `handle_event()` method. Whenever you receive an event from Slack (see the previous section), you can call this method with the JSON-encoded string containing the event, and a `slack::token` object that contains the necessary access tokens Engine will need to perform actions in response to this event.

If you are using Luna to handle HTTP requests, then your HTTP endpoint handler might look like this:

```cpp
    luna::server server;
    slack::http_event_client event_handler{"abcdef"}; //construct with verification token
    
    server.handle_request(request_method::POST, "/slack/event", [&](auto req) -> response
    {
        if (!req.body.empty())
        {
            // Get the token object from our persistence layer. Note that this will require deserializing the
            // JSON object passed to us to discover the team id. Anyway, you'll need to implement this function
            // yourself ;)
            // Notice that this is only necessary if you want to call the Web API in your event handlers. If you don't
            // care about being able to do that, just pass in an empty token object and don't sweat persistence.
            auto token = fetch_token_for_team(req.body);
            
            return {event_handler.handle_event(req.body, token)}; // returns an empty string
        }
        
        else if (!req.params["event"].empty())
        {
            // This is for that one time that Slack will check whether your HTTP endpoint works.
            slack::token token; // no need for an actual token here.
            return {handler_.handle_event(req.params["event"], token)}; // returns a non-empty string that must be put into the response body
        }
        
        // in case this is not what we were expecting
        return {404};
    });
```

# Handling events

Once you've got your HTTP server and `slack::http_event_client` wired up, handling events is straightforward. You can write an event handler for each message type that you have subscribed to, and you can also write an event handler for any message that was not otherwise handled or recognized as a fallback. To attach an event handler to Engine, you can call `slack::http_event_client::on()`. `on()` is a templated function—you pass the event type to handle as the template parameter. The one and only function parameter is a `std::functional`-style callback that will do the event handling. For example, if we want to listen to `user_typing` events, we could do the following:

```cpp
    event_handler.on<slack::event::user_typing>([](auto event, const auto &envelope)
    {
        // `event` is a shared pointer to an event object.
        // `envelope` contains the `token` object we passed in when we received the event, among other things
        std::cout << "User " << event->user << " is typing in channel " << event->channel << std::endl;
    });
```

## SPECIAL NOTE

Not all events are available in Engine at this time. We are adding events periodically, but because this is a manual process, until Slack exposes information on the structure of events that can be used to programmatically generate these class definitions, it's gonna be slow going :frowning:.

# Handling messages

Messages are just one kind of event in the Slack ontology, but it is a very special kind of event. For this reason, in addition to the event handlers described above, Engine also provides some specialized message handling functionality to allow you to filter messages that you want to listen for based on a regex.

For example, if you wanted to make a friendly bot that greeted everyone that said "hello", you could use the `hears()` method to make that happen, instead of writing a `message` event handler. It's more convenient this way!

```cpp
    event_handler.hears("hello", [](const auto &message)
    {
        std::cout << "Received message from " << message.from_user_id << " in channel " << message.channel_id << "\"" << message.text << "\"" << std::endl;
        message.reply("Howdy!");
    });
```

The first parameter is regex to match what is heard by your bot, and the second is a simplified `std::functional`-style callback that you provide. The `slack::message` object that is passed to your callback provides a convenience method for sending replies—provided that you gave `slack::http_event_client` a fully-loaded `token` object from your access token store when you first recieved the event.

Notice that you will receive message from _all_ user, including yourself, unless you filter them out. A future version of Engine will filter out your own messages for you.

Future versions of Engine will provide more sophisticated message threading functionality, to help you keep track of conversational context as your app engages in multiple conversational exchanges with users.