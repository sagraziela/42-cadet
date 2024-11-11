#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include "./utils.hpp"
# include "./Contact.hpp"

class PhoneBook
{
    private:
            Contact _contacts[8];
            int _index;

    public:
            PhoneBook(void);
            ~PhoneBook(void);
            void add(void);
            void search(void);
};

#endif
