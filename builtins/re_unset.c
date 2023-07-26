#include "minishell.h"

int	validate(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| str[i] == '_'))
		i++;
	if (i != ft_strlen(str))
		return (0);
	return (1);
}

void	delete_var(t_data *data, char **new, int x)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (i != x)
			new[j++] = ft_strdup(data->env[i]);
		i++;
	}
	new[j] = NULL;
	ft_freearr(data->env);
}

int	get_var(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(str, data->env[i], ft_strlen(str)))
			if (data->env[i][ft_strlen(str)] == '='
				|| !data->env[i][ft_strlen(str)])
				return (i);
		i++;
	}
	return (-1);
}

char	**update_env(t_data *data, char *str)
{
	char	**new;
	int		i;

	i = get_var(data, str);
	if (i == -1)
		return (data->env);
	new = malloc(sizeof(char *) * ft_tabsize(data->env));
	if (!new)
		exit(EXIT_FAILURE);
	delete_var(data, new, i);
	return (new);
}

void	re_unset(char **args, t_data *data)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!validate(args[i]))
		{
			fd_printf(STDERR_FILENO, ERR_INVALID_IDENT, "unset", args[i]);
			data->exit_status = EXIT_FAILURE;
		}
		else
			data->env = update_env(data, args[i]);
		i++;
	}
}
