/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:39:52 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/13 16:36:57 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minitalk.h"

void	handler(int signo, siginfo_t *info, void *other)
{
	int	bit;
	int	current;

	bit = 0;
	current = 0;
	(void)info;
	(void)other;
	while (bit < 8)
	{
		if (signo == SIGUSR1)
			current += 0 << bit;
		else if (signo == SIGUSR2)
			current += 1 << bit;
		bit++;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %i\n\n", getpid());
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
	return (0);
}
