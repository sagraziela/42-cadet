/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:32:43 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/15 13:40:55 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minitalk_bonus.h"

int	g_delivered = 0;

void	signal_delivery(int signo)
{
	if (signo == SIGUSR1)
	{
		g_delivered = 1;
		ft_printf("Signal delivered\n");
	}
}

void	send_signal(unsigned char octet, int pid)
{
	int				i;
	unsigned char	bit;

	i = 0;
	while (i < 8)
	{
		g_delivered = 0;
		bit = (octet >> i & 1);
		if (bit == 0)
			kill(pid, SIGUSR1);
		else if (bit == 1)
			kill(pid, SIGUSR2);
		i++;
		while (!g_delivered)
			;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;
	int					i;

	pid = 0;
	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		sa.sa_handler = signal_delivery;
		sa.sa_flags = 0;
		sigaction(SIGUSR1, &sa, NULL);
		while (argv[2][i] != '\0')
		{
			send_signal(argv[2][i], pid);
			i++;
		}
	}
	return (0);
}
