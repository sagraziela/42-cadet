/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:27:17 by gde-souz          #+#    #+#             */
/*   Updated: 2024/11/28 15:30:45 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ClapTrap.hpp"

int main(void)
{
    ClapTrap A("John");
    ClapTrap B("Billy");

    B.attack("John");
    B.takeDamage(1);
    B.beRepaired(1);
}
