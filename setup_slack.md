---
layout: default
title: Authing against Slack
---

There are three pathways to gaining access to the Slack API, and which you choose depends upon your ultimate goals:

* Are you just getting started, and need a quick token to start development? Generate a bearer token.

* Are you wanting to deploy a one-off integration for use only by your team? Create a bot user. This is the preferred method for most integration types.

* Do you want to build a Slack App that anyone can install on their team? Create a Slack App.

# Bearer tokens

For development and testing, Slack can issue you a bearer token at https://api.slack.com/web

Please note: This token gives its bearer full access to your account. Keep it secret. Keep it safe.

Please also note: These tokens are for development and testing only.

Find the team you want the token for in the list; then click "Create token" to generate the token. It should have the form `xoxp-1234-5678-9abc`. Copy that down somewhere for use in your Slack app.

# Bot users

Bot users are special free users designed for use by integrations. They have limited access to your Slack team, and are clearly identified as a bot, and are therefore ideal for deploying a one-off integration internally. [Create a new bot](https://my.slack.com/services/new/bot) to generate a bot token of the form `xoxb-1234-5678-9abc`.

[More information about what bot users are.](https://api.slack.com/bot-users)

# Slack Apps

Slack Apps are the best way to get your application used by anyone. It requires a good deal more infrastructural support on your part because Slack Apps use OAuth2 to generate access token for each team that installs your app. [It's easy to get started](https://api.slack.com/applications/new) building a Slack App. There is also a C++ Slack App SDK called [Redstone](https://github.com/DEGoodmanWilson/redstone), built upon Engine, under development to help make this process easier!