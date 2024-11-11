/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:06:18 by root              #+#    #+#             */
/*   Updated: 2024/11/11 13:24:03 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./PhoneBook.hpp"

int main(void)
{
    PhoneBook pb;
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
        if (std::cin.eof())
        {
            std::cout << std::endl;
            return (0);
        }
    }
    return (0);
}