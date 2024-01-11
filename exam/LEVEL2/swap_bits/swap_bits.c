/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:01:29 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/17 12:01:26 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned char	swap_bits(unsigned char octet)
{
	unsigned char	res;

	res = (octet >> 4) | (octet << 4);
	printf("%u\n", res);
	return (res);
}

int	main(void)
{
	unsigned char	ch;

	ch = 'a';
	printf("%u\n", ch);
	swap_bits(ch);
}

// unsigned char	swap_bits(unsigned char octet)
// {
// 	unsigned char	result;

// 	result = (octet >> 4) | (octet << 4);
// 	return (result);
// }
