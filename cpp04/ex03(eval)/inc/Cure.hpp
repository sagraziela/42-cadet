/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:34:03 by mortins-          #+#    #+#             */
/*   Updated: 2024/10/30 08:40:35 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

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

class Cure : public AMateria {
	public:
		// Constructors
		Cure( void );
		Cure( const Cure &_cure );

		// Destructor
		~Cure( void );

		// Operator overloads
		Cure &operator = ( const Cure &_cure );

		// Methods
		virtual AMateria*	clone( void ) const;
		virtual void		use( ICharacter& target );
};

#endif
