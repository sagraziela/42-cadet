/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:23:58 by gde-souz          #+#    #+#             */
/*   Updated: 2024/11/25 15:47:21 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name)
{
    this->_Name = name;
    std::cout << name << " was created.\n";
}

ClapTrap::~ClapTrap(void)
{
    std::cout << this->_Name << " was destroyed.\n";
}

void ClapTrap::attack(const std::string& target)
{
    std::cout << "ClapTrap " << this->_Name;
    std::cout << " attacks " << target;
    std::cout << ", causing " << this->_Hit << " point(s) of damage!\n";
}

void ClapTrap::takeDamage(unsigned int amount)
{
    this->_Hit -= amount;
    std::cout << "ClapTrap " << this->_Name;
    std::cout << " takes damage of " << amount << " point(s).\n";
}

void ClapTrap::beRepaired(unsigned int amount)
{
    this->_Hit += amount;
    std::cout << "ClapTrap " << this->_Name;
    std::cout << " is repaired with " << amount << " point(s).\n";
    std::cout << "Now it has the total of " << this->_Hit << " Hit point(s).\n";
}
