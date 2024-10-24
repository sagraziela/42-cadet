/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:57:08 by root              #+#    #+#             */
/*   Updated: 2024/10/07 13:36:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Zombie.hpp"

Zombie::Zombie(void)
{
    this->_name = "(null)";
    std::cout << this->_name << " was created." << std::endl;
}

Zombie::~Zombie()
{
    std::cout << this->_name << " was destroyed." << std::endl;
}

void    Zombie::announce( void )
{
    std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void    Zombie::setName(std::string str)
{
    this->_name = str;
}
