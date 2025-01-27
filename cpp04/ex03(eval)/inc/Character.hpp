/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:45:34 by mortins-          #+#    #+#             */
/*   Updated: 2024/10/30 14:54:49 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <iostream>
# include "ICharacter.hpp"

# define BOLD "\e[1m"
# define ITALIC "\e[3m"
# define UNDERLINE "\e[4m"
# define RED "\e[91m"
# define GREEN "\e[92m"
# define YELLOW "\e[93m"
# define BLUE "\e[94m"
# define PURPLE "\e[95m"
# define CYAN "\e[96m"
# define INVERT "\e[90m\e[107m"
# define RESET "\e[0m"

class Character : public ICharacter {
	private:
		std::string	name;
		AMateria	*backpack[4];
		AMateria	*dump[10];

		Character( void );

	public:
		// Constructors
		Character( std::string name );
		Character( const Character &_character );

		// Destructor
		~Character( void );

		// Operator overloads
		Character &operator = ( const Character &_character );

		// Getters
		virtual const std::string&	getName( void ) const;

		// Methods
		virtual void	equip( AMateria* m );
		virtual void	unequip( int idx );
		virtual void	use( int idx, ICharacter& target );
};

#endif
