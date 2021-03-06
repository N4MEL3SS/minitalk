/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celadia <celadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:59:29 by celadia           #+#    #+#             */
/*   Updated: 2022/02/01 15:59:29 by celadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void	close_server(int sig)
{
	(void)sig;
	write(1, "\nThe server is stopped.\n", 24);
	exit(EXIT_SUCCESS);
}

void	print_pid(int pid)
{
	char	pid_chr;
	int		i;

	i = 10000;
	if (pid / i == 0)
		i = 1000;
	while (i)
	{
		pid_chr = (char)(pid / i + 48);
		write(1, &pid_chr, 1);
		pid %= i;
		i /= 10;
	}
	write(1, "\n", 1);
}

static void	get_msg(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	byte;
	static int				bit;

	(void)ucontext;
	if (sig == SIGUSR1)
		byte += 1 << (7 - bit);
	if (++bit == 8)
	{
		write(1, &byte, 1);
		if (byte == '\n')
			kill(info->si_pid, SIGUSR2);
		bit = 0;
		byte = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			mask;

	if (sigemptyset(&mask) == -1
		|| sigaddset(&mask, SIGUSR1) == -1
		|| sigaddset(&mask, SIGUSR2) == -1)
		exit(EXIT_FAILURE);
	sa.sa_mask = mask;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = get_msg;
	signal(SIGINT, close_server);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (-1);
	print_pid(getpid());
	while (1)
		pause();
	return (0);
}
