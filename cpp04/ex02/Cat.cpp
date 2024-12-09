#include "./Cat.hpp"

Cat::Cat(std::string type) : Animal(type)
{
	this->brain = new Brain();
    std::cout << this->_type << " Cat was created.\n";
}

Cat::Cat() : Animal()
{
    this->_type= "default";
    std::cout << "Default Cat was created.\n";
}

Cat::Cat(Cat const &src) : Animal(src)
{
	std::cout << "Cat copy constructor called.\n";
	*this = src;
}

Cat &Cat::operator=(Cat const &src)
{
	std::cout << "Cat copy assignment operator called.\n";
	if (this != &src)
	{
		this->_type = src._type;
	}
	return *this;
}

Cat::~Cat()
{
	delete this->brain;
    std::cout << this->_type << " Cat was destroyed.\n";
}

void Cat::makeSound() const
{
	std::cout << "Miau! 🐱\n";
}
