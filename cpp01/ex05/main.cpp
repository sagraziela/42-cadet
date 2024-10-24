/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:09:52 by root              #+#    #+#             */
/*   Updated: 2024/10/21 15:34:05 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Harl.hpp"

int main(void)
{
    Harl boy;

    boy.complain("DEBUG");
    boy.complain("INFO");
    boy.complain("WARNING");
    boy.complain("ERROR");
    boy.complain("HAHA");
    return (0);
}