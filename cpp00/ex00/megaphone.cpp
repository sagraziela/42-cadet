#include <iostream>

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        std::cout << "" << argv[1];
        std::cout << "\n";
        return (0);
    }
    return (1);
}

// c++ -Wall -Wextra -Werror -g -std=c++98 megaphone.cpp
