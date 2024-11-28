/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:20:07 by root              #+#    #+#             */
/*   Updated: 2024/11/28 13:16:52 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Fixed.hpp"

const int   Fixed::_frac = 8;

Fixed::Fixed(void)
{
    this->_nbr = 0;
    //std::cout << "Default constructor called." << std::endl;
}

Fixed::Fixed(const int val)
{
    this->_nbr = (val << this->_frac);
    //std::cout << "INT constructor called." << std::endl;
}

Fixed::Fixed(const float val)
{
    this->_nbr = roundf(val * (1 << _frac));
    //std::cout << "Float constructor called." << std::endl;
}

Fixed::~Fixed(void)
{
    //std::cout << "Destructor called." << std::endl;
}

Fixed::Fixed(Fixed const &copy)
{
    *this = copy;
    //std::cout << "Copy constructor called." << std::endl;
}

Fixed &Fixed::operator = (Fixed const &copy)
{
	if (this != &copy)
		this->_nbr = copy.getRawBits();
    //std::cout << "Copy assignment operator called\n";
	return *this;
}

float Fixed::toFloat( void ) const
{
    return ((float)_nbr / (1 << _frac));
}

int Fixed::toInt( void ) const
{
    return (roundf(_nbr >> _frac));
}

int Fixed::getRawBits(void) const
{
    //std::cout << "getRawBits member function called" << std::endl;
    return (this->_nbr);
}

void Fixed::setRawBits(int const raw)
{
    this->_nbr = raw;
    //std::cout << "setRawBits member function called" << std::endl;
}

Fixed Fixed::operator+(Fixed const &nbr) const
{
	return (Fixed(this->toFloat() + nbr.toFloat()));
}

Fixed Fixed::operator-(Fixed const &nbr) const
{
	return (Fixed(this->toFloat() - nbr.toFloat()));
}

Fixed Fixed::operator*(Fixed const &nbr) const
{
	return (Fixed(this->toFloat() * nbr.toFloat()));
}

Fixed Fixed::operator/(Fixed const &nbr) const
{
	return (Fixed(this->toFloat() / nbr.toFloat()));
}

bool Fixed::operator<(Fixed const &nbr) const
{
	return (this->_nbr < nbr.getRawBits());
}

bool Fixed::operator>(Fixed const &nbr) const
{
	return (this->_nbr > nbr.getRawBits());
}

bool Fixed::operator<=(Fixed const &nbr) const
{
	return (this->_nbr <= nbr.getRawBits());
}

bool Fixed::operator>=(Fixed const &nbr) const
{
	return (this->_nbr >= nbr.getRawBits());
}

bool Fixed::operator==(Fixed const &nbr) const
{
	return (this->_nbr == nbr.getRawBits());
}

bool Fixed::operator!=(Fixed const &nbr) const
{
	return (this->_nbr != nbr.getRawBits());
}

std::ostream &operator<<(std::ostream &o, Fixed const &i)
{
	o << i.toFloat();
	return o;
}

//pre-incrementers
Fixed Fixed::operator++()
{
    this->_nbr++;
    return (*this);
}

Fixed Fixed::operator--()
{
    this->_nbr--;
    return (*this);
}

// pos-increments
Fixed Fixed::operator++(int)
{
    Fixed dup (*this);
    this->_nbr++;
    return (dup);
}

Fixed Fixed::operator--(int)
{
    Fixed dup (*this);
    this->_nbr--;
    return (dup);
}

// comparators
Fixed &Fixed::min(Fixed &a, Fixed &b)
{
    return (a > b ? b : a);
}

Fixed const &Fixed::min(Fixed const &a, Fixed const &b)
{
    return (a > b ? b : a);
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
    return (a > b ? a : b);
}

Fixed const &Fixed::max(Fixed const &a, Fixed const &b)
{
    return (a > b ? a : b);
}
