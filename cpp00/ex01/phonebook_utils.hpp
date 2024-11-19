#ifndef PHONEBOOK_UTILS_HPP
# define PHONEBOOK_UTILS_HPP

# include <iostream>
# include <iomanip>
# include "./Contact.hpp"
# include "./PhoneBook.hpp"

std::string fit_str(std::string str);
std::string print_details(Contact contact, std::string str);
int         is_list_full(Contact *contact, int index, int oldest);

#endif
