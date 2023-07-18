/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:01:26 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/04 14:22:28 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	value_inquotes(t_data *data, int i)
{
	int	j;

	j = 0;
	printf("declare -x ");
	while (data->env[i][j])
	{
		printf("%c", data->env[i][j]);
		if (data->env[i][j] == '=')
			break ;
		j++;
	}
	printf("%c%s%c\n", '"', data->env[i] + j + 1, '"');
}

int	check_var(t_data *data, char *str)
{
	int	i;
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '=')
			break ;
		j++;
	}
	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(str, data->env[i], j))
			if (data->env[i][j] == '=' || !data->env[i][j])
				return (i);
		i++;
	}
	return (-1);
}

int	valid_ident(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
		{
			ft_dprintf(STDERR_FILENO, ERR_INVALID_IDENT, "export", str);
			return (1);
		}
		i++;
	}
	if (!i || (str[0] >= '0' && str[0] <= '9') || str[i] == SPACE)
	{
		ft_dprintf(STDERR_FILENO, ERR_INVALID_IDENT, "export", str);
		return (1);
	}
	return (0);
}

void	sort_env(t_data *data)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (data->env[i])
	{
		j = i + 1;
		while (data->env[j])
		{
			if (ft_strcmp(data->env[i], data->env[j]) > 0)
			{
				tmp = data->env[i];
				data->env[i] = data->env[j];
				data->env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	cd_home(t_data *data)
{
	char	*path;
	int		i;

	if (!check_home(data))
	{
		ft_dprintf(STDERR_FILENO, ERR_UNSET, "HOME");
		data->exit_status = EXIT_FAILURE;
	}
	else
	{
		set_oldpwd(data);
		path = ft_getenv(data, "HOME");
		i = chdir(path);
		if (i)
		{
			ft_dprintf(STDERR_FILENO, ERR_NO_SUCH_FILE_2, "cd", path);
			data->exit_status = EXIT_FAILURE;
			return ;
		}
		set_pwd(data);
		free(path);
	}
}
