#include "minishell.h"

void	set_oldpwd(t_data *data)
{
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp("OLDPWD", data->env[i], 6) && data->env[i][6] == '=')
		{
			free(data->env[i]);
			data->env[i] = ft_strcjoin("OLDPWD", '=', cwd);
		}
		i++;
	}
	free(cwd);
}

void	set_pwd(t_data *data)
{
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp("PWD", data->env[i], 3) && data->env[i][3] == '=')
		{
			free(data->env[i]);
			data->env[i] = ft_strcjoin("PWD", '=', cwd);
		}
		i++;
	}
	free(cwd);
}

int	check_home(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp("HOME", data->env[i], 4))
			if (data->env[i][4] == '=' || !data->env[i][4])
				return (1);
		i++;
	}
	return (0);
}

void	re_cd(char **args, t_data *data)
{
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	if (!args[1])
		cd_home(data);
	else if (!ft_strcmp(args[1], "-"))
		cd_oldpwd(data);
	else if (ft_strcmp(args[1], "."))
	{
		set_oldpwd(data);
		i = chdir(args[1]);
		if (i == -1)
		{
			fd_printf(2, CUSTOM_2, "cd", args[1], strerror(errno));
			data->exit_status = 1;
			free(cwd);
			return ;
		}
		set_pwd(data);
	}
	else if (!cwd)
		fd_printf(2, "cd: error retrieving current directory: getcwd:\
		cannot access parent directories: No such file or directory\n");
	free(cwd);
}
