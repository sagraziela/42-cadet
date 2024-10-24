/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook_utils.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:21:27 by root              #+#    #+#             */
/*   Updated: 2024/10/01 14:17:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./phonebook_utils.hpp"

std::string fit_str(std::string str, size_t max)
{
    size_t  len;

    len = str.size();
    if (len > max)
    {
        str.resize(max);
        str[max - 1] = '.';
    }
    else if (len < max)
    {
        while (len++ < max)
            std::cout << " ";
    }
    return (str);
}

void    print_list_contacts(Contact contacts[8])
{
    int i;
    std::string str;

    i = 0;
    str = "";
    std::cout << "|----------|----------|----------|----------|" << std::endl;
    std::cout << "|     INDEX|FIRST NAME| LAST NAME|  NICKNAME|" << std::endl;
    std::cout << "|----------|----------|----------|----------|" << "\n";
    while (i < 8)
    {
        if (contacts[i].get_fname().size())
        {
            std::cout << "|         " << i << "|";
            str = fit_str(contacts[i].get_fname(), 10);
            std::cout << str << "|";
            str = fit_str(contacts[i].get_lname(), 10);
            std::cout << str <<  "|";
            str = fit_str(contacts[i].get_nick(), 10);
            std::cout << str << "|" << std::endl;
        }
        i++;
    }
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

int is_list_full(Contact contact, int index)
{
    std::string str;

    str = "";
    if (index >= 8)
    {
        std::cout << "-------------------------------------------------------" << std::endl;
        std::cout << "You have reached the limit of 8 contacts." << std::endl;
        std::cout << "If you add another contact, the oldest one of your list will be excluded." << std::endl;
        std::cout << "The oldest contact of your list is: " << contact.get_fname() << " " << contact.get_lname() << std::endl;
        std::cout << "-------------------------------------------------------\n" << std::endl;
        std::cout << "Are you sure you want to continue? (y/n) > ";
        if (std::getline(std::cin, str) && str != "y")
            return (1);
    }
    return (0);
}
