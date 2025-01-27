/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:46:02 by mortins-          #+#    #+#             */
/*   Updated: 2024/10/30 11:47:36 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MateriaSource.hpp"

// Default constructor
MateriaSource::MateriaSource( void ) {
	// std::cout << "MateriaSource default constructor called" <<std::endl;
	for (int i = 0; i < 4; i++)
		materia[i] = NULL;
}

// Copy constructor
MateriaSource::MateriaSource( const MateriaSource &_materiasource ) {
	// std::cout << "MateriaSource copy constructor called" << std::endl;
	for (int i = 0; i < 4; i++) {
		if (_materiasource.materia[i])
			materia[i] = _materiasource.materia[i]->clone();
		else
			materia[i] = NULL;
	}
}

// Destructor
MateriaSource::~MateriaSource( void ) {
	// std::cout << "MateriaSource destructor called" <<std::endl;
	for (int i = 0; i < 4; i++) {
		if (materia[i] != NULL)
			delete materia[i];
	}
}

// -----------------------------------Operators---------------------------------
// Copy assignment operator overload
MateriaSource& MateriaSource::operator = ( const MateriaSource &_materiasource ) {
	// std::cout << "MateriaSource copy assignment operator called" << std::endl;
	if (this != &_materiasource) {
		for (int i = 0; i < 4; i++) {
			if (_materiasource.materia[i])
				materia[i] = _materiasource.materia[i]->clone();
			else {
				delete materia[i];
				materia[i] = NULL;
			}
		}
	}
	return (*this);
}

// -----------------------------------Methods-----------------------------------
void	MateriaSource::learnMateria( AMateria *m ) {
	if (m == NULL)
	{
		std::cout << "Error: Materia does not exist!" << std::endl;
		return ;
	}
	for (int i = 0; i < 4; i++) {
		if (materia[i] == NULL) {
			this->materia[i] = m;
			std::cout << "MateriaSource: Learned " << m->getType() << std::endl;
			return;
		}
	}
	delete m;
	std::cerr << "Error: MateriaSource is full" << std::endl;
}

AMateria*	MateriaSource::createMateria( const std::string& type ) {
	if (!type[0]) {
		std::cerr << "Error: Empty type not allowed" << std::endl;
		return NULL;
	}
	for (int i = 0; i < 4; i++) {
		if (materia[i] != NULL && materia[i]->getType() == type)
			return (materia[i]->clone());
	}
	std::cerr << "Error: MateriaSource doesn't know requested materia" << std::endl;
	return NULL;
}