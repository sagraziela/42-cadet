/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 07:48:58 by mortins-          #+#    #+#             */
/*   Updated: 2024/10/30 12:34:00 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
# define AMATERIA_HPP

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

class ICharacter;

class AMateria {
	protected:
		std::string type;

	public:
		// Constructors
		AMateria( void );
		AMateria( const std::string & _type );
		AMateria( const AMateria &_amateria );

		// Destructor
		virtual ~AMateria( void );

		// Operator overloads
		AMateria &operator = ( const AMateria &_amateria );

		// Getters
		std::string const & getType( void ) const;


		// Methods
		virtual			AMateria* clone( void ) const = 0;
		virtual void	use( ICharacter& target );
};

#endif
