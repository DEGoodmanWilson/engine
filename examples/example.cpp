#include <iostream>
#include <slack/slack.h>

using namespace std;
using namespace slack;

int main()
{
    cout << "Hello, World!" << endl;

    //This is how it should go
    ::slack::slack s{"xoxp-1234"};
    auto response = s.chat.postMessage("channel", "message");

    cout << response->message->text << endl;

    return 0;
}