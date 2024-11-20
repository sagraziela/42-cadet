/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:42:43 by root              #+#    #+#             */
/*   Updated: 2024/11/20 11:43:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Zombie.hpp"

Zombie* zombieHorde(int N, std::string name);

int main(void)
{
    int    size = 20;
    Zombie *horde = zombieHorde(size, "ZzZzzomb");

    for (int i = 0; i < size; i++)
    {
        horde[i].announce();
    }
    delete [] horde;
}