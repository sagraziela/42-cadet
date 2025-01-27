/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fire.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:34:22 by mortins-          #+#    #+#             */
/*   Updated: 2024/10/30 11:08:31 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Fire.hpp"

// Default constructor
Fire::Fire( void ) : AMateria("fire") {
	// std::cout << "Fire default constructor called" <<std::endl;
}

// Copy constructor
Fire::Fire( const Fire &_fire ) : AMateria("fire") {
	// std::cout << "Fire copy constructor called" << std::endl;
	*this = _fire;
}

// Destructor
Fire::~Fire( void ) {
	// std::cout << "Fire destructor called" <<std::endl;
}

// -----------------------------------Operators---------------------------------
// Copy assignment operator overload
Fire& Fire::operator = ( const Fire &_fire ) {
	// std::cout << "Fire copy assignment operator called" << std::endl;
	if (this != &_fire)
		*this = _fire;
	return (*this);
}

// -----------------------------------Methods-----------------------------------
AMateria*	Fire::clone( void ) const {
	return (new Fire());
}

void	Fire::use( ICharacter& target ) {
	std::cout << "* shoots an fire bolt at " << target.getName() << "*" << std::endl;
}
