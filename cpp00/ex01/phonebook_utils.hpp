#ifndef PHONEBOOK_UTILS_HPP
# define PHONEBOOK_UTILS_HPP

# include <iostream>
# include <iomanip>
# include "./Contact.hpp"
# include "./PhoneBook.hpp"

# define MAX_CONTACTS 3

std::string fit_str(std::string str);
std::string print_details(Contact contact, std::string str);
int         is_list_full(Contact contact[MAX_CONTACTS], int index);

#endif
