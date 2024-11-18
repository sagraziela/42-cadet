/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:54:26 by gde-souz          #+#    #+#             */
/*   Updated: 2024/11/18 15:54:36 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./PhoneBook.hpp"

PhoneBook::PhoneBook(void)
{
    this->_index = 0;
    std::cout << \
            "Welcome to Crappy! It was created an empty phonebook for up to " << MAX_CONTACTS << " contacts.\n" \
            << std::endl;
}

PhoneBook::~PhoneBook(void)
{
    std::cout << "See you soon! 👋" << std::endl;
}

void    PhoneBook::add(void)
{
    std::string str;

    str = "";
    if (is_list_full(this->_contacts, this->_index))
        return ;
    else if (this->_index == MAX_CONTACTS)
        this->_index = 0;
    while (str == "") {
        std::cout << "Enter the contact's 1st name > ";
        if (!std::getline(std::cin, str)) {
            if (std::cin.eof()) {
                std::cout << "Input ended (Ctrl+D or EOF). Exiting...\n";
                exit(EXIT_FAILURE);
            } else if (std::cin.fail()) {
                std::cout << "Input error or interrupted (Ctrl+C). Exiting...\n";
                std::cin.clear(); 
                //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                exit(EXIT_FAILURE);
            }
            
        } else if (str != "") {
            this->_contacts[this->_index].set_fname(str);
        }
    }
    str = "";
    while (!std::cin.eof() && str == "")
    {
        std::cout << "Enter the contact's last name > ";
        if (std::getline(std::cin, str) && str != "")
            this->_contacts[this->_index].set_lname(str);
        else if (std::cin.eof())
            return ;
    }
    str = "";
    while (!std::cin.eof() && str == "")
    {
        std::cout << "Enter the contact's nickname > ";
        if (std::getline(std::cin, str) && str != "")
            this->_contacts[this->_index].set_nick(str);
        else if (std::cin.eof())
            return ;
    }
    str = "";
    while (!std::cin.eof() && str == "")
    {
        std::cout << "Enter the phone number > ";
        if (std::getline(std::cin, str) && str != "")
            this->_contacts[this->_index].set_phone_num(str);
        else if (std::cin.eof())
            return ;
    }
    str = "";
    while (!std::cin.eof() && str == "")
    {
        std::cout << "Enter the darkest secret > ";
        if (std::getline(std::cin, str) && str != "")
            this->_contacts[this->_index].set_secret(str);
        else if (std::cin.eof())
            return ;
    }
    std::cout << "THE CONTACT WAS SUCESSFULLY SAVED!" << std::endl;
    this->_index++;
}

void    PhoneBook::print_list_contacts(void)
{
    std::string str;

    str = "";
    std::cout << "|----------|----------|----------|----------|" << std::endl;
    std::cout << "|" << std::setw(10) << "INDEX"
            << "|" << std::setw(10) << "FIRST NAME"
            << "|" << std::setw(10) << "LAST NAME"
            << "|" << std::setw(10) << "NICKNAME"
            << "|" << std::endl;
    std::cout << "|----------|----------|----------|----------|" << std::endl;
    for (int i = 0; (i < MAX_CONTACTS && this->_contacts[i].get_fname().size()); i++)
    {
        std::cout << "|" << std::setw(10) << i << "|";
        str = fit_str(this->_contacts[i].get_fname());
        std::cout << str << "|";
        str = fit_str(this->_contacts[i].get_lname());
        std::cout << str <<  "|";
        str = fit_str(this->_contacts[i].get_nick());
        std::cout << str << "|" << std::endl;
    }
}

void    PhoneBook::search(void)
{
    std::string str;

    if (this->_index < 1)
    {
        std::cout << "The list is still empty." << std::endl;
        return ;
    }
    print_list_contacts();
    while (!std::cin.eof() && str == "")
    {
        str = "";
        std::cout << "Enter the index of a contact to see its details [0-" << MAX_CONTACTS << "] > ";
        if (std::getline(std::cin, str) && str != "")
        {
            if (!str[1] && str[0] >= 48 && str[0] <= 48 + MAX_CONTACTS)
            {
                str = print_details(this->_contacts[str[0] - 48], str);
            }
            else
            {
                std::cout << "THE INDEX " << str << " DOES NOT EXIST." << std::endl;
                str = "";
            }
        }
    }
}
