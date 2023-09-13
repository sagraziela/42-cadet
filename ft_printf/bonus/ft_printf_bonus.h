/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:09:57 by gde-souz          #+#    #+#             */
/*   Updated: 2023/09/13 15:45:40 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdarg.h>
# include "../libft/libft.h"

# define DECIMAL    "0123456789"
# define HEXALOW    "0123456789abcdef"
# define HEXAUP     "0123456789ABCDEF"
# define DATA_TYPES "cspdiuxX%"
# define FLAGS      "-0.# +"

int		ft_printf(const char *str, ...);
int		check_data_type(char type, va_list args);
int		ft_putnbr_base(long long nbr, char *base);
int		apply_plus_space(char **flag);
int		check_flags(char *flag, va_list args);

#endif