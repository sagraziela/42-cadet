/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:46:11 by root              #+#    #+#             */
/*   Updated: 2024/11/21 15:32:37 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

std::string    replace_str(std::string str, const std::string& toFind, const std::string& toReplace)
{
    int i = 0;

    while (str.find(toFind, i) != std::string::npos)
    {
        i = str.find(toFind, i);
        str.erase(i, toFind.length());
        str.insert(i, toReplace);
        i += toReplace.length();
    }
    return str;
}

int main(int argc, char **argv)
{
    std::ifstream   infile(argv[1]);
    
    std::string     str;
    char            c;
    
    if (argc != 4)
    {
        std::cout << "Usage:\n<FILENAME> <STR1> <STR2>\n\n";
        return 1;
    }
    if (!infile.is_open())
        return (std::cout << "Error: " << argv[1] << " file not found.\n", 1);
    
    std::string     filename = std::string(argv[1]).append(".replace");
    std::ofstream   outfile(filename.c_str());
    
    if (!outfile.is_open())
		return (std::cout << "Error: failed to create output file.\n", infile.close(), 1);
    while (std::getline(infile, str))
    {
        str = replace_str(str, argv[2], argv[3]);
        outfile << str;
        if (!infile.eof())
            outfile << '\n';
    }
    outfile.close();
    infile.close();
    return 0;
}
