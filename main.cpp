#include <iostream>
#include "slack.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "USAGE: " << argv[0] << " xoxb-token-here" << std::endl;
        exit(-1);
    }

    std::string token = argv[1];


    slack::set_token(token);

    std::cout << slack::auth.test();

    return 0;
}