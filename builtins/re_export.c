/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:56:26 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/02 10:22:46 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_var(t_data *data, char *str, int j)
{
	int	i;

	if (!ft_strchr(str, '='))
		return ;
	i = 0;
	while (data->env[i])
	{
		if (i == j)
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(str);
		}
		i++;
	}
}

char	**add_var(t_data *data, char *str)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (ft_tabsize(data->env) + 2));
	i = 0;
	while (data->env[i])
	{
		new[i] = ft_strdup(data->env[i]);
		free(data->env[i]);
		i++;
	}
	free(data->env);
	new[i++] = ft_strdup(str);
	new[i] = NULL;
	return (new);
}

void	export_var(t_data *data, char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (!valid_ident(args[i]))
		{
			j = check_var(data, args[i]);
			if (j == -1)
				data->env = add_var(data, args[i]);
			else
				edit_var(data, args[i], j);
		}
		else
			data->exit_status = EXIT_FAILURE;
		i++;
	}
}

void	export_declare(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strchr(data->env[i], '='))
			printf("declare -x %s\n", data->env[i]);
		else
			value_inquotes(data, i);
		i++;
	}
}

void	re_export(char **args, t_data *data)
{
	if (args[1])
	{
		export_var(data, args);
		sort_env(data);
	}
	else
		export_declare(data);
}
