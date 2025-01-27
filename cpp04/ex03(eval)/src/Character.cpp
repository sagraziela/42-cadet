/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:45:58 by mortins-          #+#    #+#             */
/*   Updated: 2024/10/30 12:43:17 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Character.hpp"

// Default constructor
Character::Character( void ) {
	// std::cout << "Character default constructor called" <<std::endl;
	for (int i = 0; i < 10; i++) {
		if (i < 4)
			backpack[i] = NULL;
		dump[i] = NULL;
	}
}

// Constructor
Character::Character( std::string _name ) : name(_name) {
	for (int i = 0; i < 10; i++) {
		if (i < 4)
			backpack[i] = NULL;
		dump[i] = NULL;
	}
}

// Copy constructor
Character::Character( const Character &_character ) {
	// std::cout << "Character copy constructor called" << std::endl;
	name = _character.name;

	for (int i = 0; i < 10; i++) {
		if (i < 4)
			backpack[i] = NULL;
		dump[i] = NULL;
	}

	for (int i = 0; i < 4; i++) {
		if (_character.backpack[i] != NULL)
			backpack[i] = _character.backpack[i]->clone();
	}

}

// Destructor
Character::~Character( void ) {
	// std::cout << "Character destructor called" <<std::endl;
	for (int i = 0; i < 10; i++) {
		if (i < 4 && backpack[i] != NULL)
			delete backpack[i];
		if (dump[i] != NULL)
			delete dump[i];
	}
}

// -----------------------------------Operators---------------------------------
// Copy assignment operator overload
Character& Character::operator = ( const Character &_character ) {
	// std::cout << "Character copy assignment operator called" << std::endl;
	name = _character.name;

	for (int i = 0; i < 10; i++) {
		if (i < 4 && backpack[i] != NULL)
			delete backpack[i];
		if (dump[i] != NULL)
			delete dump[i];
	}

	for (int i = 0; i < 10; i++) {
		if (i < 4 && _character.backpack[i] != NULL)
			backpack[i] = _character.backpack[i]->clone();
		else if (i < 4)
			backpack[i] = NULL;
		dump[i] = NULL;
	}
	return (*this);
}

// -----------------------------------Getters-----------------------------------
const std::string& Character::getName( void ) const {
	return (name);
}

// -----------------------------------Methods-----------------------------------
void	Character::equip( AMateria* m ) {
	if (m == NULL)
		return;
	for (int i = 0; i < 4; i++) {
		if (backpack[i] == NULL) {
			std::cout << name << "[" << i << "] equipped " << m->getType() << std::endl;
			backpack[i] = m;
			return;
		}
	}
	delete m;
	std::cerr << "Error: Backpack is already full" << std::endl;
}

void	Character::unequip( int idx ) {
	if (idx < 0 || idx > 3)
		std::cerr << "Error: Invalid materia index" << std::endl;
	else if (!backpack[idx])
		std::cerr << "Error: Requested index is empty" << std::endl;
	else {
		for (int i = 0; i < 10; i++) {
			if (dump[i] == NULL) {
				std::cout << name << "[" << idx << "] unequipped " << backpack[idx]->getType() << std::endl;
				dump[i] = backpack[idx];
				backpack[idx] = NULL;
				return;
			}
		}
		for (int i = 0; i < 10; i++) {
			if (dump[i] != NULL)
				delete dump[i];
		}
		std::cout << name << "[0] unequipped " << backpack[0]->getType() << std::endl;
		dump[0] = backpack[idx];
		backpack[idx] = NULL;
		for (int i = 1; i < 10; i++)
			dump[i] = NULL;
	}
}

void	Character::use( int idx, ICharacter& target ) {
	if (idx < 0 || idx > 3)
		std::cerr << "Error: Invalid materia index" << std::endl;
	else if (!backpack[idx])
		std::cerr << "Error: Requested index is empty" << std::endl;
	else
		backpack[idx]->use(target);
}