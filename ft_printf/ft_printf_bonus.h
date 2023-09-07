/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:09:57 by gde-souz          #+#    #+#             */
/*   Updated: 2023/09/07 16:46:03 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdarg.h>
# include "./libft/libft.h"

# define DECIMAL    "0123456789"
# define HEXALOW    "0123456789abcdef"
# define HEXAUP     "0123456789ABCDEF"

int	ft_printf(const char *str, ...);

#endif