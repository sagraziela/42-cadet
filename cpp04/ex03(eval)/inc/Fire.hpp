/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fire.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:34:07 by mortins-          #+#    #+#             */
/*   Updated: 2024/10/30 15:00:10 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIRE_HPP
# define FIRE_HPP

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

class Fire : public AMateria {
	public:
		// Constructors
		Fire( void );
		Fire( const Fire &_fire );

		// Destructor
		~Fire( void );

		// Operator overloads
		Fire &operator = ( const Fire &_fire );

		// Methods
		virtual AMateria*	clone( void ) const;
		virtual void		use( ICharacter& target );
};

#endif
