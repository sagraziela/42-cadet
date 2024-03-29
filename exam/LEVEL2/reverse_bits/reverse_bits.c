/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:02:21 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/12 12:45:40 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char	result;
	int				i;

	i = 8;
	while (i--)
	{
		result = result * 2 + (octet % 2);
		octet /= 2;
	}
	return (result);
}

int	main(void)
{
	printf("Result: %u\n", reverse_bits(1));
}

// unsigned char	reverse_bits(unsigned char octet)
// {
// 	int				i;
// 	unsigned char	result;

// 	i = 8;
// 	while (i--)
// 	{
// 		result = result * 2 + (octet % 2);
// 		octet /= 2;
// 	}
// 	return (result);
// }
