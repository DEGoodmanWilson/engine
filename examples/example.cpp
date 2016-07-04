#include <iostream>
#include <slack/slack.h>

using namespace std;
using namespace slack;

int main()
{
    cout << "Hello, World!" << endl;

    //This is how it should go
    ::slack::slack s{"xoxp-1234"};
    auto message = s.chat.postMessage("channel", "message");

    cout << message << endl;

    return 0;
}