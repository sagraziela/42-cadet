/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:06:18 by root              #+#    #+#             */
/*   Updated: 2024/11/19 14:07:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./PhoneBook.hpp"
#include <csignal>

void handle_signal(int signal)
{
    std::cerr << "\nPrograma interrompido de forma abrupta.\n";
    std::exit(signal);
}

int main(void)
{
    PhoneBook pb;
    std::string str;
    
    std::signal(SIGINT, handle_signal);
    
    while(1)
    {
        std::cout << "What do you want to do? Enter ADD, SEARCH or EXIT > ";
        if (!std::getline(std::cin, str) || std::cin.eof() || std::cin.fail())
        {
            std::cout << std::endl;
            std::exit(EXIT_FAILURE);
        }
        if (str == "ADD")
            pb.add();
        if (str == "SEARCH")
            pb.search();
        if (str == "EXIT")
            std::exit(EXIT_SUCCESS);
    }
    return (0);
}