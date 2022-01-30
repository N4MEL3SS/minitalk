#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

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
	unsigned char	*msg;

	if (argc != 3)
	{
		write(1, "Error, need two parameters: PID and Message\n", 44);
		return (0);
	}
	pid = atoi(argv[1]);
	msg = (unsigned char *)argv[2];
	while (*msg)
		send_msg(pid, *msg++);
	return (0);
}
