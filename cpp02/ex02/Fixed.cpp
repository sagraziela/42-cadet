/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:20:07 by root              #+#    #+#             */
/*   Updated: 2024/11/26 12:58:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Fixed.hpp"

const int   Fixed::_frac = 8;

Fixed::Fixed(void)
{
    this->_nbr = 0;
    std::cout << "Default constructor called." << std::endl;
}

Fixed::Fixed(const int val)
{
    this->_nbr = (val << this->_frac);
    std::cout << "INT constructor called." << std::endl;
}

Fixed::Fixed(const float val)
{
    this->_nbr = roundf(val * (1 << _frac));
    std::cout << "Float constructor called." << std::endl;
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
	if (this != &copy)
		this->_nbr = copy.getRawBits();
    std::cout << "Copy assignment operator called\n";
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
    std::cout << "getRawBits member function called" << std::endl;
    return (this->_nbr);
}

void Fixed::setRawBits(int const raw)
{
    this->_nbr = raw;
    std::cout << "setRawBits member function called" << std::endl;
}

Fixed Fixed::operator+(Fixed const &rhs) const
{
	return (Fixed(this->toFloat() + rhs.toFloat()));
}

Fixed Fixed::operator-(Fixed const &rhs) const
{
	return (Fixed(this->toFloat() - rhs.toFloat()));
}

Fixed Fixed::operator*(Fixed const &rhs) const
{
	return (Fixed(this->toFloat() * rhs.toFloat()));
}

Fixed Fixed::operator/(Fixed const &rhs) const
{
	return (Fixed(this->toFloat() / rhs.toFloat()));
}

Fixed Fixed::operator<(Fixed const &rhs) const
{
	return (Fixed(this->toFloat() < rhs.getRawBits()));
}

Fixed Fixed::operator>(Fixed const &rhs) const
{
	return (Fixed(this->toFloat() > rhs.getRawBits()));
}

Fixed Fixed::operator<=(Fixed const &rhs) const
{
	return (Fixed(this->toFloat() <= rhs.getRawBits()));
}

Fixed Fixed::operator>=(Fixed const &rhs) const
{
	return (Fixed(this->toFloat() >= rhs.getRawBits()));
}

Fixed Fixed::operator==(Fixed const &rhs) const
{
	return (Fixed(this->toFloat() == rhs.getRawBits()));
}

Fixed Fixed::operator!=(Fixed const &rhs) const
{
	return (Fixed(this->toFloat() != rhs.getRawBits()));
}

std::ostream &operator<<(std::ostream &o, Fixed const &i)
{
	o << i.toFloat();
	return o;
}

//ADD OPERADORES
