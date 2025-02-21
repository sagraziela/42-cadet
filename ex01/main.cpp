/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:27:17 by gde-souz          #+#    #+#             */
/*   Updated: 2024/12/02 14:16:18 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ClapTrap.hpp"
#include "./ScavTrap.hpp"

int main(void)
{
    ClapTrap A("Billy");

    A.attack("John");
    A.takeDamage(5);
    A.beRepaired(1);
}
