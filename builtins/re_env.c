#include "minishell.h"

void	re_env(char **args, t_data *data)
{
	int	i;

	(void) args;
	i = -1;
	while (data->env[++i])
	{
		if (!ft_strncmp(data->env[i], "PATH=", 5))
		{
			i = -1;
			break ;
		}
	}
	if (i != -1)
	{
		fd_printf(STDERR_FILENO, ERR_NO_SUCH_FILE, "env");
		data->exit_status = 127;
		return ;
	}
	while (data->env[++i])
		if (ft_strchr(data->env[i], '='))
			printf("%s\n", data->env[i]);
}
