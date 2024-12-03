/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:27:17 by gde-souz          #+#    #+#             */
/*   Updated: 2024/12/03 13:19:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ClapTrap.hpp"
#include "./ScavTrap.hpp"

int main(void)
{
    ScavTrap A("John");

    A.attack("Billy");
    A.takeDamage(5);
    A.beRepaired(1);
    A.guardGate();
}
