#include "./MateriaSource.hpp"

MateriaSource::MateriaSource()
{
    for (int i = 0; i < SIZE; i++)
		this->_inventory[i] = NULL;
    //std::cout << "Default MateriaSource was created.\n";
}

MateriaSource::MateriaSource(MateriaSource const &src)
{
	for (int i = 0; i < SIZE; i++)
	{
		this->_inventory[i] = NULL;
		if (src._inventory[i] != NULL)
			this->_inventory[i] = src._inventory[i]->clone();
	}
	//std::cout << "MateriaSource copy constructor called.\n";
}

MateriaSource &MateriaSource::operator=(MateriaSource const &src)
{
	//std::cout << "MateriaSource copy assignment operator called.\n";
	if (this != &src)
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (this->_inventory[i] != NULL)
				delete (this->_inventory[i]);
			this->_inventory[i] = NULL;
			if (src._inventory[i] != NULL)
				this->_inventory[i] = src._inventory[i]->clone();
		}
	}
	return *this;
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < SIZE; i++)
	{
		if (this->_inventory[i] != NULL)
			delete this->_inventory[i];
	}
    //std::cout << "MateriaSource was destroyed.\n";
}

void MateriaSource::learnMateria(AMateria *m)
{
	if (m == NULL)
	{
		std::cout << "Materia does NOT exist!" << std::endl;
		return ;
	}
	for (int i = 0; i < SIZE; i++)
	{
		if (this->_inventory[i] == NULL)
		{
			this->_inventory[i] = m;
			return ;
		}
	}
	delete m;
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
	if (!type[0]) {
		std::cout << "Empty type NOT allowed.\n";
		return NULL;
	}
	for (int i = 0; i < SIZE; i++)
	{
		if (this->_inventory[i] != NULL
			&& this->_inventory[i]->getType() == type)
			return (this->_inventory[i]->clone());
	}
	std::cout << "NO template materia found for type: " << type << std::endl;
	return (NULL);
}
