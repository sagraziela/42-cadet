/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:27:17 by gde-souz          #+#    #+#             */
/*   Updated: 2024/12/02 12:12:58 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ClapTrap.hpp"

int main(void)
{
    ClapTrap A("John");
    ClapTrap B("Billy");

    B.attack("John");
    B.takeDamage(5);
    B.beRepaired(1);
}
