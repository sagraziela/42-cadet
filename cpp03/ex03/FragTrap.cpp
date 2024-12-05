/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:39:26 by root              #+#    #+#             */
/*   Updated: 2024/12/05 12:06:14 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./FragTrap.hpp"

FragTrap::FragTrap(void) : ClapTrap()
{
	this->_name = "(null)";
	this->_hit = 100;
	this->_energy = 100;
	this->_attackDamage = 30;
    std::cout << "Default FragTrap was created.\n";
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	this->_name = name;
	this->_hit = 100;
	this->_energy = 100;
	this->_attackDamage = 30;
    std::cout << this->_name << " FragTrap was created.\n";
}

FragTrap::FragTrap(FragTrap const &src) : ClapTrap(src)
{
	std::cout << "FragTrap copy constructor called.\n";
	*this = src;
}

FragTrap &FragTrap::operator=(FragTrap const &src)
{
	std::cout << "FragTrap copy assignment operator called.\n";
	if (this != &src)
	{
		this->_name = src._name;
		this->_hit = src._hit;
		this->_energy = src._energy;
		this->_attackDamage = src._attackDamage;
	}
	return *this;
}

FragTrap::~FragTrap(void)
{
    std::cout << this->_name << " FragTrap was destroyed.\n";
}

void FragTrap::highFivesGuys(void)
{
	std::cout << this->_name << " FragTrap requests a HIGH FIVE.\n";
}
