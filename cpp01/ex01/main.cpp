/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:42:43 by root              #+#    #+#             */
/*   Updated: 2024/10/07 13:38:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Zombie.hpp"

Zombie* zombieHorde(int N, std::string name);

int main(void)
{
    int    size = 5;
    Zombie *horde = zombieHorde(5, "ZzZzzomb");

    for (int i = 0; i < size; i++)
    {
        horde[i].announce();
    }
    delete [] horde;
}