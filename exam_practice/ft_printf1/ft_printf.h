/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:23:33 by root              #+#    #+#             */
/*   Updated: 2024/08/21 15:21:07 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define DECIMAL "0123456789"
# define OCTAL "01234567"
# define HIGH_HEXA "0123456789ABCDEF"
# define LOW_HEXA "0123456789abcdef"

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

size_t  ft_printf(const char *str, ...);

#endif
