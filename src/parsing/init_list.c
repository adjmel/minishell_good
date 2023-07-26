#include "minishell.h"

int	get_separator(char **lx, int i)
{
	int	sep;

	sep = -1;
	if (!lx[i])
		sep = LAST_CMD;
	else if (!ft_strcmp(lx[i], "&&"))
		sep = AND_TOKEN;
	else if (!ft_strcmp(lx[i], "||"))
		sep = OR_TOKEN;
	else if (!ft_strcmp(lx[i], "|"))
		sep = PIPE_TOKEN;
	else
	{
		while (lx[i] && !ft_strcmp(lx[i], ")"))
			i++;
		sep = get_separator(lx, i);
	}
	return (sep);
}

void	level_track(char **lx, int *i, int *lvl, int p)
{
	if (!p)
	{
		while (lx[*i] && !ft_strcmp(lx[*i], "("))
		{
			(*lvl)++;
			(*i)++;
		}
	}
	else
	{
		while (lx[*i] && !ft_strcmp(lx[*i], ")"))
		{
			(*lvl)--;
			(*i)++;
		}
	}
}

void	init_list(t_data **data, char **lx)
{
	t_mini	*node;
	char	**buffer;
	int		lvl;
	int		i;

	lvl = 0;
	i = 0;
	(*data)->head = NULL;
	while (lx[i])
	{
		level_track(lx, &i, &lvl, 0);
		buffer = NULL;
		while (lx[i] && (ft_strcmp(lx[i], ")") && ft_strcmp(lx[i], "&&")
				&& ft_strcmp(lx[i], "|") && ft_strcmp(lx[i], "||")))
			buffer = arr_concate(buffer, lx[i++]);
		node = pc_new_node(buffer, get_separator(lx, i), lvl);
		pc_addback(&(*data)->head, node);
		level_track(lx, &i, &lvl, 1);
		if (lx[i])
			i++;
	}
}
