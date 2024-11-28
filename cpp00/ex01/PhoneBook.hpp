#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include <iomanip>
# include <string>
# include <cstdlib>
# include <limits>
# include "./phonebook_utils.hpp"
# include "./Contact.hpp"

# define MAX_CONTACTS 3

class PhoneBook
{
    private:
            Contact _contacts[MAX_CONTACTS];
            int _oldest;
            int _index;

    public:
            PhoneBook(void);
            ~PhoneBook(void);
            void add(void);
            void search(void);
            void print_list_contacts(void);
};

#endif
