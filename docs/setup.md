---
layout: default
title: Connecting your project to Slack
---

There are three pathways to gaining access to the Slack API, and which you choose depends upon your ultimate goals:

* Are you just getting started, and need a quick token to start development? Generate a bearer token.

* Are you wanting to deploy a one-off integration for use only by your team? Create a bot user. This is the preferred method for most integration types.

* Do you want to build a Slack App that anyone can install on their team? Create a Slack App.

## Bearer tokens

For development and testing, Slack can [issue you a bearer token](https://api.slack.com/docs/oauth-test-tokens) for any team that you are signed into.

Please note: This token gives its bearer full access to your account. Keep it secret. Keep it safe.

Please also note: These tokens are for development and testing only.

Find the team you want the token for in the list; then click "Create token" to generate the token. It should have the form `xoxp-1234-5678-9abc`. Copy that down somewhere for use in your Slack app.

## Custom bots

Custom bots are designed to allow you to create chatbots for your team that integrate with your own bespoke services and line-of-business systems. They have limited access to your Slack team, and are clearly identified as a bot, and are therefore ideal for deploying a one-off integration internally. [Create a new bot](https://my.slack.com/services/new/bot) to generate a bot token of the form `xoxb-1234-5678-9abc`.

[More information about what bot users are.](https://api.slack.com/bot-users)

## Slack Apps

Slack Apps are the best way to get your application used by anyone. It requires a good deal more infrastructural support on your part because Slack Apps use OAuth2 to generate access token for each team that installs your app. [It's easy to get started](https://api.slack.com/applications/new) building a Slack App. There is also a C++ Slack App SDK called [Redstone](https://github.com/DEGoodmanWilson/redstone), built upon Engine, under development to help make this process easier!

# Tokens and Apps

If you are using a testing token or a custom bot, you will have in your hands an _access token_ that you can use to call endpoints in the Slack [Web API](https://api.slack.com/web) directly, as well as connect to the Slack [Real-Time Messaging API](https://api.slack.com/rtm).

If you are building a Slack App, you will have a pair of credentials—a _client id_ and a _client secret_—that you will use with [OAuth2](https://api.slack.com/docs/oauth) to allow users to install your app on their team. At this time, you will need to implement the OAuth2 flow yourself, although a future release of Engine might include support for it. At the end of the OAuth2 flow you will have a token associated with a particular team that you will need to store somewhere to use. This token is necessary for accessing the Slack [Web API](https://api.slack.com/web) and the [Real-Time Messaging API](https://api.slack.com/rtm). You will automatically be granted access to the [Events API](https://api.slack.com/events-api) when the OAuth2 flow is complete, and there is no token associated with this API.