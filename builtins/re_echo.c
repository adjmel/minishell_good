#include "minishell.h"

void	print_args(char **args, int n)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("%s", args[i++]);
		if (args[i])
			printf("%c", SPACE);
	}
	if (!i || n)
		printf("\n");
}

int	only_n(char *str)
{
	if (!(*str))
		return (1);
	while (*str)
	{
		if (*str != 'n')
			return (1);
		str++;
	}
	return (0);
}

void	n_option(char **args)
{
	int	i;

	i = 1;
	if (!only_n(args[i] + 1))
	{
		while (args[i] && *args[i] == '-' && !only_n(args[i] + 1))
			i++;
		if (!args[i])
			return ;
		print_args(args + i, 0);
	}
	else
		print_args(args + i, 1);
}

void	re_echo(char **args, t_data *data)
{
	(void)data;
	if (!args[1])
		printf("\n");
	else if (args[1][0] == '-')
		n_option(args);
	else
		print_args(args + 1, 1);
}
