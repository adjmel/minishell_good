/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:54:11 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/05 02:08:54 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	separator_check(t_data *data, char **lx, int i)
{
	if (!ft_strcmp(lx[i], "||") || !ft_strcmp(lx[i], "|")
		|| !ft_strcmp(lx[i], "&&"))
	{
		if (!lx[i + 1] || !ft_strcmp(lx[i + 1], "||")
			|| !ft_strcmp(lx[i + 1], "|")
			|| !ft_strcmp(lx[i + 1], "&&"))
		{
			if (!lx[i + 1])
				ft_dprintf(2, UNEXPECTED_TOKEN, lx[i]);
			else
				ft_dprintf(2, UNEXPECTED_TOKEN, lx[i + 1]);
			data->exit_status = 258;
			return (1);
		}
	}
	return (0);
}

int	redirection_check(t_data *data, char **lx, int i)
{
	if (is_arrow(lx[i]) != -1)
	{
		if (!lx[i + 1])
		{
			ft_dprintf(2, UNEXPECTED_TOKEN, "newline");
			data->exit_status = 258;
			return (1);
		}
		else if (is_arrow(lx[i + 1]) != -1 || !ft_strcmp(lx[i + 1], "|")
			|| !ft_strcmp(lx[i + 1], "||") || !ft_strcmp(lx[i + 1], "&&"))
		{
			ft_dprintf(2, UNEXPECTED_TOKEN, lx[i + 1]);
			data->exit_status = 258;
			return (1);
		}
	}
	return (0);
}

int	quote_check(t_data *data, char *str)
{
	char	quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (!str[i])
			{
				ft_dprintf(STDERR_FILENO, UNCLOSED_QUOT);
				return (data->exit_status = 258, 1);
			}
		}
		i++;
	}
	return (0);
}

int	invalid_sep(t_data *data, char **lx, int i)
{
	if (!ft_strcmp(lx[i], "&") || !ft_strcmp(lx[0], "&&")
		|| !ft_strcmp(lx[0], "||") || !ft_strcmp(lx[0], "|"))
	{
		ft_dprintf(2, UNEXPECTED_TOKEN, lx[i]);
		data->exit_status = 258;
		return (1);
	}
	return (0);
}

int	syntax_error(t_data *data, char **lx)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (lx[i])
	{
		if (quote_check(data, lx[i]))
			return (1);
		else if (separator_check(data, lx, i))
			return (1);
		else if (invalid_sep(data, lx, i))
			return (1);
		else if (redirection_check(data, lx, i))
			return (1);
		else if (parentheses_check(data, lx, i, &x, &y))
			return (1);
		i++;
	}
	return (0);
}
