/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:45:27 by mortins-          #+#    #+#             */
/*   Updated: 2024/10/30 11:46:57 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cure.hpp"

// Default constructor
Cure::Cure( void ) : AMateria("cure") {
	// std::cout << "Cure default constructor called" <<std::endl;
}

// Copy constructor
Cure::Cure( const Cure &_cure ) : AMateria("cure") {
	// std::cout << "Cure copy constructor called" << std::endl;
	*this = _cure;
}

// Destructor
Cure::~Cure( void ) {
	// std::cout << "Cure destructor called" <<std::endl;
}

// -----------------------------------Operators---------------------------------
// Copy assignment operator overload
Cure& Cure::operator = ( const Cure &_cure ) {
	// std::cout << "Cure copy assignment operator called" << std::endl;
	if (this != &_cure)
		*this = _cure;
	return (*this);
}

// -----------------------------------Methods-----------------------------------
AMateria*	Cure::clone( void ) const {
	return (new Cure());
}

void	Cure::use( ICharacter& target ) {
	std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}