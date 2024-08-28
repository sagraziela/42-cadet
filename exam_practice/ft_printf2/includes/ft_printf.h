/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:48:52 by gde-souz          #+#    #+#             */
/*   Updated: 2024/08/28 11:36:34 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define DECIMAL "0123456789"
# define HEXA "0123456789abcdef"

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

size_t	ft_printf(const char *arg, ...);

#endif