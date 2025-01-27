/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMateriaSource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 07:52:22 by mortins-          #+#    #+#             */
/*   Updated: 2024/10/30 09:02:20 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMATERIASOURCE_HPP
# define IMATERIASOURCE_HPP

# include <iostream>
# include "AMateria.hpp"

class IMateriaSource {
	public:
		virtual ~IMateriaSource( void ) {}
		virtual void learnMateria( AMateria* m ) = 0;
		virtual AMateria* createMateria( const std::string & type ) = 0;
};

#endif