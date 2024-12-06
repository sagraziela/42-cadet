/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:23:58 by gde-souz          #+#    #+#             */
/*   Updated: 2024/12/06 12:25:41 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name)
{
    this->_name = name;
    this->_hit = 10;
    this->_energy = 10;
    this->_attackDamage = 0;
    std::cout << name << " ClapTrap was created.\n";
}

ClapTrap::ClapTrap(void)
{
    this->_name = "(null)";
    this->_hit = 10;
    this->_energy = 10;
    this->_attackDamage = 0;
    std::cout << "Default ClapTrap was created.\n";
}

ClapTrap::ClapTrap(ClapTrap const &src)
{
	std::cout << "ClapTrap copy constructor called.\n";
	*this = src;
}

ClapTrap &ClapTrap::operator=(ClapTrap const &src)
{
	std::cout << "ClapTrap copy assignment operator called.\n";
	if (this != &src)
	{
		this->_name = src._name;
		this->_hit = src._hit;
		this->_energy = src._energy;
		this->_attackDamage = src._attackDamage;
	}
	return *this;
}

ClapTrap::~ClapTrap(void)
{
    std::cout << this->_name << " ClapTrap was destroyed.\n";
}

void ClapTrap::attack(const std::string& target)
{
    if (this->_hit <= 0)
    {
        std::cout << "ClapTrap " << this->_name << "cannot attack 'cause it doesn't have any HIT points.\n";
        return ;
    }
    if (this->_energy <= 0)
    {
        std::cout << "ClapTrap " << this->_name << "cannot attack 'cause it doesn't have any ENERGY points.\n";
        return ;
    }
    this->_energy--;
    std::cout << "ClapTrap " << this->_name;
    std::cout << " attacks " << target;
    std::cout << ", causing " << this->_hit << " point(s) of damage!\n";
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (this->_hit <= 0)
    {
        std::cout << "ClapTrap " << this->_name << "is already DEAD. It has 0 HIT points.\n";
        return ;
    }
    this->_hit -= amount;
    std::cout << "ClapTrap " << this->_name;
    std::cout << " takes damage of " << amount << " point(s).\n";
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->_hit <= 0)
    {
        std::cout << "ClapTrap " << this->_name << "doesn't have energy points to get repaired.\n";
        return ;
    }
    if (this->_energy <= 0)
    {
        std::cout << "ClapTrap " << this->_name << "doesn't have energy to get repaired.\n";
        return ;
    }
    this->_hit += amount;
    std::cout << "ClapTrap " << this->_name;
    std::cout << " is repaired with " << amount << " point(s).\n";
    std::cout << "Now it has the total of " << this->_hit << " Hit point(s).\n";
}
