#include "minishell.h"

int	not_num(char *str)
{
	if (!(*str))
		return (1);
	if (*str == '-' || *str == '+')
		str++;
	if (!(*str))
		return (1);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

void	re_exit(char **args, t_data *data)
{
	fd_printf(STDERR_FILENO, "exit\n");
	if (args[1])
	{
		if (not_num(args[1]))
		{
			fd_printf(STDERR_FILENO, ERR_NUMERIC_ARG, args[1]);
			data->exit_status = 255;
			exit(data->exit_status);
		}
		else if (args[2])
		{
			fd_printf(STDERR_FILENO, ERR_TOO_MANY_ARGS);
			data->exit_status = 1;
			return ;
		}
		else
		{
			data->exit_status = ft_atoi(args[1]);
			exit(data->exit_status);
		}
	}
	exit(EXIT_SUCCESS);
}
