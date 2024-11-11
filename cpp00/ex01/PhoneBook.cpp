#include "./PhoneBook.hpp"

PhoneBook::PhoneBook(void)
{
    this->_index = 0;
    std::cout << \
            "Welcome to Crappy! Created an empty phonebook for up to 8 contacts." \
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
    if (is_list_full(this->_contacts[this->_index % 8], this->_index))
        return ;
    while (!std::cin.eof() && str == "")
    {
        std::cout << "Enter the contact's 1st name > ";
        if (std::getline(std::cin, str) && str != "")
            this->_contacts[this->_index % 8].set_fname(str);
    }
    str = "";
    while (!std::cin.eof() && str == "")
    {
        std::cout << "Enter the contact's last name > ";
        if (std::getline(std::cin, str) && str != "")
            this->_contacts[this->_index % 8].set_lname(str);
    }
    str = "";
    while (!std::cin.eof() && str == "")
    {
        std::cout << "Enter the contact's nickname > ";
        if (std::getline(std::cin, str) && str != "")
            this->_contacts[this->_index % 8].set_nick(str);
    }
    str = "";
    while (!std::cin.eof() && str == "")
    {
        std::cout << "Enter the phone number > ";
        if (std::getline(std::cin, str) && str != "")
            this->_contacts[this->_index % 8].set_phone_num(str);
    }
    str = "";
    while (!std::cin.eof() && str == "")
    {
        std::cout << "Enter the darkest secret > ";
        if (std::getline(std::cin, str) && str != "")
            this->_contacts[this->_index % 8].set_secret(str);
    }
    std::cout << "THE CONTACT WAS SUCESSFULLY SAVED!" << std::endl;
    this->_index++;
}

void    PhoneBook::search(void)
{
    int         i;
    std::string str;

    i = 0;
    print_list_contacts(this->_contacts);
    str = "";
    while (!std::cin.eof() && str == "")
    {
        std::cout << "Enter the index of a contact to see its details > ";
        if (std::getline(std::cin, str) && str != "" && !str[1] && str[0] >= 48 && str[0] <= 50)
        {
            i = str[0] - 48;
            str = print_details(this->_contacts[i], str);
        }
        else
        {
            std::cout << "THE INDEX " << str << " DOES NOT EXIST.\n";
            str = "";
        }
    }
}
