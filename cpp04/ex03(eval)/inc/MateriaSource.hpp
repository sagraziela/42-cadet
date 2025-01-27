/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:34:53 by mortins-          #+#    #+#             */
/*   Updated: 2024/10/30 08:41:32 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include <iostream>
# include "IMateriaSource.hpp"

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

class MateriaSource : public IMateriaSource {
	private:
		AMateria *materia[4];

	public:
		// Constructors
		MateriaSource( void );
		MateriaSource( const MateriaSource &_materiasource );

		// Destructor
		~MateriaSource( void );

		// Operator overloads
		MateriaSource &operator = ( const MateriaSource &_materiasource );

		// Methods
		void		learnMateria( AMateria *m );
		AMateria*	createMateria( const std::string & type );
};

#endif
