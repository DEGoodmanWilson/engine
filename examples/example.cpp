#include <iostream>
#include <string>
#include <utility>

#define SLACK_FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

namespace engine
{

// TYPES
using channel_id = std::string;
class error
{

};
/////////

namespace chat
{
    namespace postMessage
    {
        using attachment = std::string;
    }
}

// CHAT__POST_MESSAGE
class chat__post_message_
{
public:
    void set_option(const chat::postMessage::attachment& attachment) {}
    void set_option(chat::postMessage::attachment&& attachment) {}
    int execute() { return 5;}
};
//////////

// PRIVATE
namespace private_
{

template<class S, typename T>
void set_option(S &session, T &&t)
{
    session.set_option(SLACK_FWD(t));
}

template<class S, typename T, typename... Ts>
void set_option(S &session, T &&t, Ts &&... ts)
{
    set_option(session, SLACK_FWD(t));
    set_option(session, SLACK_FWD(ts)...);
}
}
//////////


// CHAT
namespace endpoints
{
class chat
{
public:
    using message = int;

    template<typename ...Os>
    message postMessage(const channel_id &channel, const std::string &text)
    {
        chat__post_message_ session; //{channel, text};
        return session.execute();
    }

    template<typename ...Os>
    message postMessage(const channel_id &channel, const std::string &text, Os &&...os)
    {
        chat__post_message_ session; //{channel, text};
        private_::set_option<decltype(session)>(session, SLACK_FWD(os)...);
        return session.execute();
    }
};
}
//////////


class slack
{
public:
    slack(const std::string & token) {};
    slack(std::string && token) {};

    ::engine::endpoints::chat chat;
};
}


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