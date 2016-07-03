#include <iostream>
#include <slack/slack.h>

using namespace std;
using namespace engine;

int main()
{
    cout << "Hello, World!" << endl;

    //This is how it should go
    slack s{"xoxp-1234"};
    auto message = s.chat.postMessage("channel", "message", chat::postMessage::attachment{"hi"});

    cout << message << endl;

    return 0;
}