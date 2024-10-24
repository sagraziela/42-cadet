/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:46:11 by root              #+#    #+#             */
/*   Updated: 2024/10/15 14:06:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

int compare(std::string str, char *arg, int i)
{
    int pos;

    pos = 0;
    if (str[i] == arg[pos])
    {
        while (arg[pos] && str[i + pos] == arg[pos])
            pos++;
        if (!arg[pos])
            i += pos - 1;
    }
    return i;
}

void    replace_str(std::string str, char **argv)
{
    std::ofstream   outfile;
    int             pos;

    outfile.open((std::string(argv[1]) + ".replace").c_str());
    for (int i = 0; str[i] != '\0'; i++)
    {
        pos = compare(str, argv[2], i);
        if (pos > i)
        {
            for (int j = 0; argv[3][j]; j++)
                outfile << argv[3][j];
            i = pos;
        }
        else
            outfile << str[i];
    }
    outfile.close();
}

int main(int argc, char **argv)
{
    std::ifstream   infile;
    std::string     str;
    char            c;
    
    if (argc != 4)
    {
        std::cout << "You should give 3 parameters in order to execute this program." << std::endl;
        return 1;
    }
    infile.open(argv[1]);
    // ADD ERRO NA ABERTURA DO ARQUIVO
    while (!infile.eof() && infile >> std::noskipws >> c)
        str += c;
    replace_str(str, argv);
    infile.close();
    return 0;
}
