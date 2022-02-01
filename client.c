/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celadia <celadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:32:36 by celadia           #+#    #+#             */
/*   Updated: 2022/02/01 16:54:05 by celadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	short int			sign;
	unsigned long		result;

	result = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		++str;
	if (*str == '-' && ++str)
		sign = -1;
	else if (*str == '+')
		++str;
	while ('0' <= *str && *str <= '9')
	{
		result = result * 10UL + (unsigned long)*str - 48UL;
		++str;
	}
	if (result > 9223372036854775807 && sign == 1)
		return (-1);
	if (result > 9223372036854775807 && sign == -1)
		return (0);
	return ((int)result * sign);
}

void	send_msg(int pid, unsigned char c)
{
	int		bit;
	int		ret;

	bit = 8;
	while (--bit > -1)
	{
		if (c & (1 << bit))
			ret = kill(pid, SIGUSR1);
		else
			ret = kill(pid, SIGUSR2);
		if (ret || usleep(50))
		{
			write(1, "Error, message send fail!\n", 26);
			exit(EXIT_FAILURE);
		}
	}
}

int	main(int argc, char *argv[])
{
	int				pid;
	unsigned char	*msg;

	if (argc != 3)
	{
		write(1, "Error, need two parameters: PID and Message\n", 44);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	msg = (unsigned char *)argv[2];
	while (*msg)
		send_msg(pid, *msg++);
	send_msg(pid, '\n');
	return (0);
}
