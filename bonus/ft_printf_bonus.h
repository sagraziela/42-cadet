/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:09:57 by gde-souz          #+#    #+#             */
/*   Updated: 2023/09/14 13:48:28 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft/libft.h"

# define DECIMAL    "0123456789"
# define HEXALOW    "0123456789abcdef"
# define HEXAUP     "0123456789ABCDEF"
# define DATA_TYPES "cspdiuxX%"
# define FLAGS      "-0.# +"

int		ft_printf(const char *str, ...);
int		ft_putnbr_base(long long nbr, char *base);
int		handle_flags(char *flag, va_list args);

#endif