#include "./Dog.hpp"

Dog::Dog(std::string type) : Animal(type)
{
    std::cout << this->_type << " Dog was created.\n";
}

Dog::Dog(void) : Animal()
{
    this->_type= "(null)";
    std::cout << "Default Dog was created.\n";
}

Dog::Dog(Dog const &src) : Animal(src)
{
	std::cout << "Dog copy constructor called.\n";
	*this = src;
}

Dog &Dog::operator=(Dog const &src)
{
	std::cout << "Dog copy assignment operator called.\n";
	if (this != &src)
	{
		this->_type = src._type;
	}
	return *this;
}

Dog::~Dog(void)
{
    std::cout << this->_type << " was destroyed.\n";
}
