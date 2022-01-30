#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void	confirm_msg(int sig)
{
	(void)sig;
}

void	send_msg(int pid, unsigned char c)
{
	int		bit;
	int 	ret;

	bit = 8;
	while (--bit > -1)
	{
		if (c & (1 << bit))
			ret = kill(pid, SIGUSR1);
		else
			ret = kill(pid, SIGUSR2);
		if (ret || usleep(20))
		{
			write(1, "Error, message send fail!\n", 26);
			exit(EXIT_FAILURE);
		}
	}
}

int main(int argc, char *argv[])
{
	int				pid;
	short 			msg_len;
	unsigned char	*msg;

	if (argc != 3)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	msg_len = strlen(argv[2]);
	pid = atoi(argv[1]);
	msg = (unsigned char *)argv[2];
	signal(SIGUSR2, confirm_msg);
	while (*msg)
		send_msg(pid, *msg++);
	while (1)
		pause();
	return (0);
}
