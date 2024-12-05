/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:39:26 by root              #+#    #+#             */
/*   Updated: 2024/12/05 11:30:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
    this->_hit = 100;
    this->_energy = 50;
    this->_attackDamage = 20;
    std::cout << this->_name << " ScavTrap was created.\n";
}

ScavTrap::ScavTrap(void) : ClapTrap()
{
    this->_hit = 100;
    this->_energy = 50;
    this->_attackDamage = 20;
    std::cout << "Default ScavTrap was created.\n";
}

ScavTrap::ScavTrap(ScavTrap const &src) : ClapTrap(src)
{
	std::cout << "ScavTrap copy constructor called.\n";
	*this = src;
}

ScavTrap &ScavTrap::operator=(ScavTrap const &src)
{
	std::cout << "ScavTrap copy assignment operator called.\n";
	if (this != &src)
	{
		this->_name = src._name;
		this->_hit = src._hit;
		this->_energy = src._energy;
		this->_attackDamage = src._attackDamage;
	}
	return *this;
}

ScavTrap::~ScavTrap(void)
{
    std::cout << this->_name << " ScavTrap was destroyed.\n";
}

void ScavTrap::attack(const std::string& target)
{
    if (this->_hit <= 0)
    {
        std::cout << "ScavTrap " << this->_name << "cannot attack 'cause it doesn't have any HIT points.\n";
        return ;
    }
    if (this->_energy <= 0)
    {
        std::cout << "ScavTrap " << this->_name << "cannot attack 'cause it doesn't have any ENERGY points.\n";
        return ;
    }
    this->_energy--;
    std::cout << "ScavTrap " << this->_name;
    std::cout << " attacks " << target;
    std::cout << ", causing " << this->_hit << " point(s) of damage!\n";
}

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap is now in gate keeper mode.\n";
}
