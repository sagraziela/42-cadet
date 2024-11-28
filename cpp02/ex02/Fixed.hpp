/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:42:10 by root              #+#    #+#             */
/*   Updated: 2024/11/28 13:16:03 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <string>
# include <cmath>

class Fixed
{
    private:
        int _nbr;
        static const int _frac;

    public:
        Fixed(void);
        ~Fixed(void);
        Fixed(Fixed const &copy);
        Fixed &operator = (Fixed const &copy);

        Fixed(const int val);
        Fixed(const float val);
        float toFloat( void ) const;
        int toInt( void ) const;
        
        int getRawBits(void) const;
        void setRawBits(int const raw);

        // overloads
        Fixed operator+(Fixed const &nbr) const;
        Fixed operator-(Fixed const &nbr) const;
        Fixed operator*(Fixed const &nbr) const;
        Fixed operator/(Fixed const &nbr) const;
        bool operator<(Fixed const &nbr) const;
        bool operator>(Fixed const &nbr) const;
        bool operator<=(Fixed const &nbr) const;
        bool operator>=(Fixed const &nbr) const;
        bool operator==(Fixed const &nbr) const;
        bool operator!=(Fixed const &nbr) const;

        //pre-increment
        Fixed operator++();
		Fixed operator--();

        //pos-increment
		Fixed operator++(int);
		Fixed operator--(int);

        // comparators
        static Fixed &min(Fixed &a, Fixed &b);
        static Fixed const &min(Fixed const &a, Fixed const &b);
        static Fixed &max(Fixed &a, Fixed &b);
        static Fixed const &max(Fixed const &a, Fixed const &b);
};

std::ostream &operator<<(std::ostream &o, Fixed const &i);

#endif
