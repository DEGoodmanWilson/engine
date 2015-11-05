#include <iostream>
#include "plaid.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "USAGE: " << argv[0] << " xoxb-token-here" << std::endl;
        exit(-1);
    }

    std::string token = argv[1];

    cout << "Hello, World!" << endl;

    slack::plaid api{token};

    std::cout << api.auth.test();

    return 0;
}