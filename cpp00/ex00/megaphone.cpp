#include <iostream>

int main(int argc, char **argv)
{
    int     i;
    int     j;
    char    c;

    i = 1;
    if (argc == 1)
    {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
        return (1);
    }
    while (argv[i])
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] >= 97 && argv[i][j] <= 122)
                c = argv[i][j] - 32;
            else 
                c = argv[i][j];
            std::cout << "" << c;
            j++;
        }
        i++;
    }
    std::cout << "\n";
    return (0);
}
