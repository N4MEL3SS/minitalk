#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

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
}

static void	get_msg(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char 	byte;
	static int				bit;

	(void)ucontext;
	if (sig == SIGUSR1)
	{
		byte += 1 << (7 - bit);
	}
	if (++bit == 8)
	{
		write(1, &byte, 1);
		kill(info->si_pid, SIGUSR2);
		bit = 0;
		byte = 0;
	}
}

void	close_server(int sig)
{
	(void)sig;
	write(1, "\nClose\n", 7);
	exit(EXIT_SUCCESS);
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
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
