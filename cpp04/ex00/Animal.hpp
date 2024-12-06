#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

class Animal
{
    protected:
        std::string _type;

    public:
        Animal(std::string name);
        Animal(void);
        Animal(Animal const &src);
		Animal &operator=(Animal const &src);
        ~Animal(void);

        void makeSound(void);
};

#endif