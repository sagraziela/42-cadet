/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:27:46 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/21 13:34:03 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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

static void	apply_split(char **arr, char const *s, char c)
{
	int		i;
	int		j;
	int		src;

	i = 0;
	j = 0;
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
			if (!arr[j])
			{
				free(arr);
				break ;
			}
			j++;
		}
	}
	arr[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	apply_split(arr, s, c);
	return (arr);
}
