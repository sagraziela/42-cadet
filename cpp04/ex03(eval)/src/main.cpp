/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:03:18 by mortins-          #+#    #+#             */
/*   Updated: 2024/10/30 15:01:28 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Character.hpp"
#include "../inc/Cure.hpp"
#include "../inc/Ice.hpp"
#include "../inc/Fire.hpp"
#include "../inc/MateriaSource.hpp"

int	main( void ) {
	{ // Invalid materia index on player
		std::cout << INVERT << "use materia[-1]:" << RESET << std::endl;
		Character	crash("crash");
		Character	neo("Dr Neo Cortex");

		crash.use(-1, neo);
	}
	{ // Empty materia index on player
		std::cout << std::endl << INVERT << "use empty materia:" << RESET << std::endl;
		Character	crash("crash");
		Character	neo("Dr Neo Cortex");

		crash.use(0, neo);
	}
	{ // Create/equip NULL materia
		std::cout << std::endl << INVERT << "Create/equip NULL materia:" << RESET << std::endl;
		MateriaSource mat;
		Character	crash("crash");

		crash.equip(mat.createMateria(""));
	}
	{ // Full backpack
		std::cout << std::endl << INVERT << "Full backpack:" << RESET << std::endl;
		MateriaSource	mat;
		Character		crash("crash");
		mat.learnMateria(new Ice());
		for (int i = 0; i < 4; i++) {
			crash.equip(mat.createMateria("ice"));
		}
		crash.equip(mat.createMateria("ice"));
	}
	{ // Character deep copy
		std::cout << std::endl << INVERT << "Character deep copy:" << RESET << std::endl;
		MateriaSource	mat;
		Character		crash("crash");
		Character		neo("Dr Neo Cortex");

		mat.learnMateria(new Ice());
		for (int i = 0; i < 4; i++)
			crash.equip(mat.createMateria("ice"));
		{
			std::cout << YELLOW << "creating copy characters" << RESET << std::endl;
			Character	fake_crash(crash);
			Character	faker_crash = crash;
			std::cout << YELLOW << "killing copy characters" << RESET << std::endl;
		}
		crash.use(0, neo);
	}
	{ // Materia deep copy
		std::cout << std::endl << INVERT << "Materia deep copy:" << RESET << std::endl;
		MateriaSource	mat;
		Ice *ice = new Ice();
		{
			std::cout << YELLOW << "creating copy materias" << RESET << std::endl;
			Ice	*ice1 = ice;
			Ice	*ice2(ice);
			ice1->getType();
			ice2->getType();
			std::cout << YELLOW << "deleting copy materias" << RESET << std::endl;
		}
		mat.learnMateria(ice);
	}
	{ // MateriaSource deep copy
		std::cout << std::endl << INVERT << "MateriaSource deep copy:" << RESET << std::endl;
		MateriaSource	mat;
		Character		crash("crash");

		mat.learnMateria(new Ice());
		{
			std::cout << YELLOW << "creating copy MateriaSources" << RESET << std::endl;
			MateriaSource	mat1 = mat;
			MateriaSource	mat2(mat);
			std::cout << YELLOW << "deleting copy MateriaSources" << RESET << std::endl;
		}
		crash.equip(mat.createMateria("ice"));
	}
	{ // Materia does not exist
		std::cout << std::endl << INVERT << "Materia does not exist:" << RESET << std::endl;
		MateriaSource	mat;
		Character	crash("crash");

		mat.learnMateria(new Ice());
		crash.equip(mat.createMateria("aku aku"));
	}
	{ // MateriaSource is full
		std::cout << std::endl << INVERT << "MateriaSource is full" << RESET << std::endl;
		MateriaSource	mat;

		mat.learnMateria(new Cure());
		mat.learnMateria(new Ice());
		mat.learnMateria(new Ice());
		mat.learnMateria(new Cure());
		mat.learnMateria(new Ice());
	}
	{ // External materia
		std::cout << std::endl << INVERT << "External materia" << RESET << std::endl;
		MateriaSource	mat;
		Character		crash("crash");
		Character		neo("Dr Neo Cortex");

		mat.learnMateria(new Fire());
		crash.equip(mat.createMateria("fire"));
		crash.use(0, neo);
	}
	{ // Unequip leaks
		std::cout << std::endl << INVERT << "Unequip:" << RESET << std::endl;
		MateriaSource	mat;
		Character		crash("crash");
		Character		neo("Dr Neo Cortex");

		mat.learnMateria(new Ice());
		for (int i = 0; i < 4; i++)
			crash.equip(mat.createMateria("ice"));
		crash.unequip(0);
		std::cout << BOLD << "Empty: " << RESET;
		crash.use(0, neo);
		std::cout << BOLD << "Other: " << RESET;
		crash.use(1, neo);
		crash.equip(mat.createMateria("ice"));
		crash.use(0, neo);
	}
}