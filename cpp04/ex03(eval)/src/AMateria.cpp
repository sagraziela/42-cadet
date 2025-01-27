/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:46:07 by mortins-          #+#    #+#             */
/*   Updated: 2024/10/30 08:48:22 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/AMateria.hpp"

// Default constructor
AMateria::AMateria( void ) : type(NULL) {
	// std::cout << "AMateria default constructor called" <<std::endl;
}

// Constructor
AMateria::AMateria( const std::string &_type ) : type(_type) {
	// std::cout << "AMateria constructor called" << std::endl;
}

// Copy constructor
AMateria::AMateria( const AMateria &_amateria ) {
	// std::cout << "AMateria copy constructor called" << std::endl;
	*this = _amateria;
}

// Destructor
AMateria::~AMateria( void ) {
	// std::cout << "AMateria destructor called" <<std::endl;
}

// -----------------------------------Operators---------------------------------
// Copy assignment operator overload
AMateria& AMateria::operator = ( const AMateria &_amateria ) {
	// std::cout << "AMateria copy assignment operator called" << std::endl;
	if (this != &_amateria) {
		*this = _amateria;
	}
	return (*this);
}

// -----------------------------------Getters-----------------------------------
const std::string& AMateria::getType( void ) const{
	return (type);
}

// -----------------------------------Methods-----------------------------------
void	AMateria::use( ICharacter &target ){
	(void) target;
}



