/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:30:54 by root              #+#    #+#             */
/*   Updated: 2024/08/21 16:06:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"
#include <stdio.h>

int	main(void)
{
	int		nbr;
	//long	ln;
	char 	*str;
	int		original;
	int		mine;

	nbr = -42;
	//ln = -2147483650;
	str = "hello world";
	original = printf("hello %d %% %s | %p | %o | %x\n", nbr, str, &str, nbr, nbr);
	printf("PRINTF: %d\n", original);
	mine = ft_printf("hello %d %% %s | %p | %o | %x\n", nbr, str, &str, nbr, nbr);
	printf("FT_PRINTF: %d\n", mine);
}