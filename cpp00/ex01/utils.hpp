#ifndef PHONEBOOK_UTILS_HPP
# define PHONEBOOK_UTILS_HPP

# include <iostream>
# include "./Contact.hpp"

std::string fit_str(std::string str, size_t max);
std::string print_details(Contact contact, std::string str);
void        print_list_contacts(Contact contacts[8]);
int         is_list_full(Contact contact, int index);

#endif
