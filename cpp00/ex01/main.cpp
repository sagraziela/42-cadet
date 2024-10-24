/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:06:18 by root              #+#    #+#             */
/*   Updated: 2024/10/02 12:29:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./phonebook.hpp"

int main(void)
{
    Phonebook pb;
    std::string str;
    
    while(str != "EXIT")
    {
        std::cout << "What do you want to do? > ";
        std::getline(std::cin, str);
        std::cout << "" << str << std::endl;
        if (str == "ADD")
            pb.add();
        if (str == "SEARCH")
            pb.search();
        if (std::cin.eof()) - why is it necessary?
        {
            std::cout << std::endl;
            return (0);
        }
    }
    return (0);
}