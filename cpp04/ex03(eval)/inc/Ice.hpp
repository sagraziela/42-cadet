/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:34:07 by mortins-          #+#    #+#             */
/*   Updated: 2024/10/30 09:02:10 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
# define ICE_HPP

# include <iostream>
# include "AMateria.hpp"

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

class Ice : public AMateria {
	public:
		// Constructors
		Ice( void );
		Ice( const Ice &_ice );

		// Destructor
		~Ice( void );

		// Operator overloads
		Ice &operator = ( const Ice &_ice );

		// Methods
		virtual AMateria*	clone( void ) const;
		virtual void		use( ICharacter& target );
};

#endif
