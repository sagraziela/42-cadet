/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:55:44 by gde-souz          #+#    #+#             */
/*   Updated: 2024/12/02 14:29:17 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ScavTrap.hpp"

ScavTrap::ScavTrap()
{
    this->_name = "(null)";
    std::cout << this->_name << "constructor called\n";
}

ScavTrap::ScavTrap(std::string name)
{
    this->_name = name;
    std::cout << this->_name << "constructor called\n";
}

ScavTrap::~ScavTrap(void)
{
    std::cout << "Destructor called\n";
}

ScavTrap::ScavTrap(ScavTrap const &copy)
{
    *this = copy;
    std::cout << "Copy constructor called." << std::endl;
}


ScavTrap &ScavTrap::operator=(ScavTrap const &toCopy)
{
    std::cout << "Copy operator called\n";
    if (this != &toCopy)
    {
        this->name = toCopy->_name;
    }
}

void ScavTrap::attack(const std::string& target)
{
    std::cout << "THIS attacks " << target << std::endl;
}
void ScavTrap::guardGate()
{
    std::cout << "ScavTrap is now in Gate keeper mode.\n";
}
