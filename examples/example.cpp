#include <iostream>
#include <slack/slack.h>

using namespace std;
using namespace slack;

int main()
{

    ::slack::access_token token{std::getenv("SLACK_TOKEN")};
    std::string channel{"#general"};
    std::string text{"This is a test!"};

    ::slack::slack s{token};
    auto response = s.chat.postMessage(channel, text);

    cout << response.message->text << endl;

    return 0;
}