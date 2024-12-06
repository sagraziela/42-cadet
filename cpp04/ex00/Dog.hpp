#ifndef DOG_HPP
# define DOG_HPP

# include <iostream>
# include <string>
# include "./Animal.hpp"

class Dog : public Animal
{
    public:
        Dog(std::string name);
        Dog(void);
        Dog(Dog const &src);
		Dog &operator=(Dog const &src);
        ~Dog(void);
};

#endif
