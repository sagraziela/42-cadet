/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:03:47 by root              #+#    #+#             */
/*   Updated: 2024/01/11 12:28:07 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	int		middle;
	char	tmp;

	i = 0;
	len = ft_strlen(str) - 1;
	middle = len / 2;
	while (i < middle)
	{
		tmp = str[i];
		printf("str[i] = %c\n", str[i]);
		str[i] = (char)str[len];
		str[len] = tmp;
		i++;
		len--;
	}
	return (str);
}

int	main(void)
{
	printf("%s\n", ft_strrev("Hello"));
	return (0);
}
