/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:39:10 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/21 12:36:30 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd(t_list **lst, void *content)
{
	t_list	*last;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = content;
	new_node->next = NULL;
	if (*lst == NULL)
	{
		new_node->prev = NULL;
		*lst = new_node;
	}
	else
	{
		last = ft_lstlast(*lst);
		new_node->prev = last;
		last->next = new_node;
	}
}

int	find_line_break(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		len_s;

	i = 0;
	len_s = 0;
	while (s[len_s] != '\0')
		len_s++;
	if ((unsigned char) c == '\0')
	{
		return ((char *)s + len_s);
	}
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
