/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook_utils.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:21:27 by root              #+#    #+#             */
/*   Updated: 2024/11/21 10:56:05 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./phonebook_utils.hpp"

std::string fit_str(std::string str)
{
    size_t  len;

    len = str.length();
    if (len > 10)
        str = str.substr(0, 9) + '.';
    else if (len < 10)
        str.insert(0, (10 - len), ' ');
    return (str);
}


std::string print_details(Contact contact, std::string str)
{
    if (contact.get_fname().size())
    {
        std::cout << "-------------------------------------------------------" << std::endl;
        std::cout << "FIRST NAME: " << contact.get_fname() << std::endl;
        std::cout << "LAST NAME: " << contact.get_lname() << std::endl;
        std::cout << "NICKNAME: " << contact.get_nick() << std::endl;
        std::cout << "PHONE NUMBER: " << contact.get_phone_num() << std::endl;
        std::cout << "DARKEST SECRET: " << contact.get_secret() << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;
    }
    else
    {
        std::cout << "THERE IS NO CONTACT SAVED IN INDEX " << str << std::endl;
        str = "";
    }
    return (str);
}

int is_list_full(Contact *contact, int index, int oldest)
{
    std::string str;

    str = "";
    if (index == MAX_CONTACTS || oldest > 0)
    {
        std::cout << "-------------------------------------------------------\n\n";
        std::cout << "You have reached the limit of " << MAX_CONTACTS << " contacts." << std::endl;
        std::cout << "If you add another contact, the oldest one of your list will be excluded." << std::endl;
        std::cout << "The oldest contact of your list is: " << contact[oldest].get_fname() << " " << contact[oldest].get_lname() << std::endl;
        std::cout << "-------------------------------------------------------\n\n";
        std::cout << "Are you sure you want to continue? (y/n) > ";
        if (std::getline(std::cin, str) && str != "y")
            return (1);
    }
    return (0);
}
