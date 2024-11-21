/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:15:49 by root              #+#    #+#             */
/*   Updated: 2024/11/21 15:46:00 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Harl.hpp"

Harl::Harl(void)
{
    std::cout << "A Harl was created." << std::endl;
}

Harl::~Harl(void)
{
    std::cout << "A Harl was destroyed." << std::endl;
}

void Harl::debug(void)
{
    std::cout << "DEBUG ::: I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!\n";
}

void Harl::info(void)
{
    std::cout << "INFO ::: I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!\n";
}

void Harl::warning(void)
{
    std::cout << "WARNING ::: I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month.\n";
}

void Harl::error(void)
{
    std::cout << "ERROR ::: This is unacceptable! I want to speak to the manager now.\n";
}

void Harl::complain(std::string level)
{    
    void		(Harl::*ptr_complain[])() = {
        &Harl::debug,
        &Harl::info,
        &Harl::warning,
        &Harl::error
    };
	std::string	list[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    for (int i = 0; i < 4; i++)
	{
		if (list[i] == level)
		{
			(this->*ptr_complain[i])();
			break ;
		}
        if (i == 3)
        {
            std::cout << "---------------------------------------------------------------\n";
            std::cout << "Sorry, Harl doesn't have any complain for the given parameter: " << level << std::endl;
            std::cout << "---------------------------------------------------------------\n";
        }
	}
}
