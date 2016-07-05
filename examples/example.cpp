#include <iostream>
#include <slack/slack.h>

using namespace std;
using namespace slack;

int main()
{

    std::string token{std::getenv("SLACK_TOKEN")};
    std::string channel{std::getenv("SLACK_CHANNEL")};
    std::string text{"This is a test!"};

    //This is how it should go
    ::slack::slack s{token};
    auto response = s.chat.postMessage(channel, text);

    cout << response->message->text << endl;

    return 0;
}