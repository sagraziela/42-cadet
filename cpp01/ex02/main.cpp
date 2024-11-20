/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:36:13 by root              #+#    #+#             */
/*   Updated: 2024/11/20 11:49:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(void)
{
    std::string str = "HI THIS IS BRAIN";
    std::string *stringPTR = &str;
    std::string &stringREF = str;

    std::cout << "str address       > " << &str << std::endl;
    std::cout << "stringPTR address > " << &stringPTR << std::endl;
    std::cout << "stringREF address > " << &stringREF << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "str value       > " << str << std::endl;
    std::cout << "stringPTR value > " << *stringPTR << std::endl;
    std::cout << "stringREF value > " << stringREF << std::endl;
}
