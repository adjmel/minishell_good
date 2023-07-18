/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:28:50 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/05 01:34:20 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_parenth_check(t_data *data, char **lx, int *x, int i)
{
	(*x)++;
	if (i && ft_strcmp(lx[i - 1], "&&") && ft_strcmp(lx[i - 1], "||")
		&& ft_strcmp(lx[i - 1], "|") && ft_strcmp(lx[i - 1], "("))
	{
		ft_dprintf(2, UNEXPECTED_TOKEN, lx[i]);
		data->exit_status = 258;
		return (1);
	}
	if (lx[i + 1] && (!ft_strcmp(lx[i + 1], ")") || !ft_strcmp(lx[i + 1], "&&")
			|| !ft_strcmp(lx[i + 1], "||") || !ft_strcmp(lx[i + 1], "||")))
	{
		ft_dprintf(2, UNEXPECTED_TOKEN, lx[i + 1]);
		data->exit_status = 258;
		return (1);
	}
	return (0);
}

int	close_parenth_check(t_data *data, char **lx, int *y, int i)
{
	(*y)++;
	if (lx[i + 1] && ft_strcmp(lx[i + 1], "&&")
		&& ft_strcmp(lx[i + 1], "||") && ft_strcmp(lx[i + 1], "|")
		&& ft_strcmp(lx[i + 1], ")"))
	{
		dprintf(2, UNEXPECTED_TOKEN, lx[i + 1]);
		data->exit_status = 258;
		return (1);
	}
	return (0);
}

int	parentheses_check(t_data *data, char **lx, int i, int *x, int *y)
{
	if (!ft_strcmp(lx[i], "("))
	{
		if (open_parenth_check(data, lx, x, i))
			return (1);
	}
	else if (!ft_strcmp(lx[i], ")"))
	{
		if (close_parenth_check(data, lx, y, i))
			return (1);
	}
	if (!lx[i + 1])
	{
		if (*x > *y)
		{
			ft_dprintf(2, UNEXPECTED_TOKEN, "(");
			return (data->exit_status = 258, 1);
		}
		else if (*x < *y)
		{
			ft_dprintf(2, UNEXPECTED_TOKEN, ")");
			return (data->exit_status = 258, 1);
		}
	}
	return (0);
}
