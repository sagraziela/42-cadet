/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:27:46 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/03 16:28:18 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_words(const char *str, char c)
{
	unsigned int	i;
	int				counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			counter++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (counter);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*memory;

	memory = (char *)malloc(sizeof(char) * n + 1);
	if (memory == NULL)
		return (NULL);
	ft_strlcpy(memory, s, n + 1);
	return (memory);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		src;
	char	**arr;

	i = 0;
	j = 0;
	arr = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		src = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > src)
		{
			arr[j] = ft_strndup(s + src, (i - src));
			j++;
		}
	}
	arr[j] = NULL;
	return (arr);
}
// ADD FREE FUNCTION