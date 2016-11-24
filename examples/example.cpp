#include <iostream>
#include <slack/slack.h>

int main()
{
    slack::web_client web_client{std::getenv("SLACK_TOKEN")};

    auto response = web_client.channels.list();

    // First we test if the response is not an error response
    if(response)
    {
        for (const auto &channel : response.channels)
        {
            std::cout << "Channel: " << channel.name << std::endl;
        }
    }
}