/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:58:49 by root              #+#    #+#             */
/*   Updated: 2024/10/08 11:10:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Weapon.hpp"

Weapon::Weapon(std::string str)
{
    this->_type = str;
}

Weapon::~Weapon(void)
{
}

std::string Weapon::getType(void)
{
    return (this->_type);
}

void    Weapon::setType(std::string str)
{
    this->_type = str;
}
