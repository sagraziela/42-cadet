/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:15:49 by root              #+#    #+#             */
/*   Updated: 2024/10/21 15:35:47 by root             ###   ########.fr       */
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
    std::cout << "DEBUG ::: I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::info(void)
{
    std::cout << "INFO ::: I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning(void)
{
    std::cout << "WARNING ::: I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
}

void Harl::error(void)
{
    std::cout << "ERROR ::: This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(std::string level)
{    
    void		(Harl::*ptr_complain[4])(void) = {
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
            std::cout << "---------------------------------------------------------------" << std::endl;
            std::cout << "Sorry, Harl doesn't have any complain for the given parameter: " << level << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl;
        }
	}
}
