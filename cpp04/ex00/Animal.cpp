#include "./Animal.hpp"

Animal::Animal(std::string type)
{
    this->_type = "(null)";
    std::cout << "Default Animal was created.\n";
}

Animal::Animal(void)
{
    std::cout << this->_type << " Animal was created.\n";
}

Animal::Animal(Animal const &src)
{
	std::cout << " Animal copy constructor called.\n";
	*this = src;
}

Animal &Animal::operator=(Animal const &src)
{
	std::cout << "Animal copy assignment operator called.\n";
	if (this != &src)
	{
		this->_type = src._type;
	}
	return *this;
}

Animal::~Animal(void)
{
    std::cout << this->_type << " was destroyed.\n";
}

void Animal::makeSound(void)
{
    std::cout << "*SOUND*\n";
}
