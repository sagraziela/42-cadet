/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:20:07 by root              #+#    #+#             */
/*   Updated: 2024/10/22 11:51:14 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Fixed.hpp"

const int   Fixed::_frac = 8;

Fixed::Fixed(void)
{
    this->_nbr = 0;
    std::cout << "Default constructor called." << std::endl;
}

Fixed::~Fixed(void)
{
    std::cout << "Destructor called." << std::endl;
}

Fixed::Fixed(Fixed const &copy)
{
    *this = copy;
    std::cout << "Copy constructor called." << std::endl;
}

Fixed &Fixed::operator = (Fixed const &copy)
{
    
}

int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return (this->_nbr);
}

void Fixed::setRawBits(int const raw)
{
    this->_nbr = raw;
    std::cout << "setRawBits member function called" << std::endl;
}
