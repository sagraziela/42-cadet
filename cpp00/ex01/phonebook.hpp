#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include "./phonebook_utils.hpp"
# include "./contact.hpp"

class Phonebook
{
    private:
            Contact _contacts[8];
            int _index;

    public:
            Phonebook(void);
            ~Phonebook(void);
            void add(void);
            void search(void);
};

#endif
