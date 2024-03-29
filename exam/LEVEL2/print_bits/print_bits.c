/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:51:19 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/12 12:41:47 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int				i;
	unsigned char	bit;

	i = 8;
	while (i--)
	{
		bit = (octet >> i & 1) + '0';
		write(1, &bit, 1);
	}
}

int	main(void)
{
	print_bits(8);
}

// void	pr_bits(unsigned char octet)
// {
// 	int				i;
// 	unsigned char	bit;

// 	while (i--)
// 	{
// 		bit = (octet >> i & 1) + 48;
// 		write(1, &bit, 1);
// 	}
// }
