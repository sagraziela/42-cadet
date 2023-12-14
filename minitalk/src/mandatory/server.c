/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:39:52 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/14 17:42:45 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minitalk.h"
#include <signal.h>

int	g_bit = 0;

void	handle_bits(int signo, siginfo_t *siginfo, void *context)
{
	unsigned char	current;

	current = 0;
	(void)context;
	if (signo == SIGUSR1)
		current += 0 << g_bit;
	else if (signo == SIGUSR2)
		current += 1 << g_bit;
	g_bit++;
	ft_printf("g_bit: %d\n", g_bit); // está chegando até o bit 8
	if (g_bit == 8)
	{
		ft_printf("%c\n", current); // não está printando o char corretamente
		g_bit = 0;
		current = 0;
	}
	kill(siginfo->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %i\n\n", getpid());
	sa.sa_sigaction = handle_bits;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
