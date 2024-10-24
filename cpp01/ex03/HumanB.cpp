/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:10:51 by root              #+#    #+#             */
/*   Updated: 2024/10/10 13:27:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./HumanB.hpp"

HumanB::HumanB(std::string name): _name(name)
{
    this->_weapon = NULL;
    std::cout << "Human " << this->_name << " was created" << std::endl;
}

HumanB::~HumanB(void)
{
    std::cout << "Human " << this->_name << " was destroyed" << std::endl;
}

void HumanB::setWeapon(Weapon &weapon)
{
    this->_weapon = &weapon;
}

void    HumanB::attack(void)
{
    if (!this->_weapon)
    {
        std::cout << this ->_name << " cannot attack because no weapon was setted " << std::endl;
        return ;
    }
    std::cout << this->_name << " attacks with their " << this->_weapon->getType() << std::endl;
}
