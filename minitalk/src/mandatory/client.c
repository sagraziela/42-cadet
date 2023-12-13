/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:32:43 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/13 17:04:43 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minitalk.h"

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;
	int					i;

	pid = 0;
	i = 0;
	ft_putstr_fd("hello, client!\n", 1);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i])
		{
			sigaction(SIGUSR1, &sa, NULL);
			sendsig(argv[2], pid);
		}
	}
	return (0);
}
