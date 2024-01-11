/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:43:22 by gde-souz          #+#    #+#             */
/*   Updated: 2023/09/27 11:01:23 by gde-souz         ###   ########.fr       */
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
	char	temp;
	int		len;
	int		i;

	len = ft_strlen(str);
	printf("Len = %i\n", len);
	i = 0;
	while (i < len / 2)
	{
		temp = str[i];
		printf("%c\n", temp);
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
		i++;
	}
	return (str);
}

int	main(void)
{
	char	*str;

	str = "Hello world!";
	printf("%s\n", str);
	ft_strrev(str);
	printf("%s\n", str);
}
