#include "minishell.h"

int	is_arrow(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (OUTPUT);
	else if (!ft_strcmp(str, ">>"))
		return (APPEND);
	else if (!ft_strcmp(str, "<"))
		return (INPUT);
	else if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	return (-1);
}

int	check_redir(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (is_arrow(args[i]) != -1)
			return (1);
		i++;
	}
	return (0);
}

void	fill_rd(t_mini *tmp, char ***buffer)
{
	t_redir	*node;
	int		i;

	i = 0;
	while (tmp->args[i])
	{
		printf("tmp args: %s\n", tmp->args[i]);
		if (is_arrow(tmp->args[i]) != -1)
		{
			node = rd_new_node(tmp->args[i + 1],
					is_arrow(tmp->args[i]));
			rd_addback(&tmp->head, node);
			i++;
		}
		else
			*buffer = arr_concate(*buffer, tmp->args[i]);
		i++;
	}
}

void	expand_files(t_data *data, t_mini *proc)
{
	t_redir	*ptr;

	ptr = proc->head;
	while (ptr)
	{
		ptr->file = expand(data, ptr->file, 1);
		if (ft_strchr(ptr->file, '\'') || ft_strchr(ptr->file, '"'))
			ptr->file = del_quote(ptr->file);
		ptr = ptr->next;
	}
}

void	init_rd(t_data *data)
{
	t_mini	*tmp;
	char	**buffer;

	tmp = data->head;
	while (tmp)
	{
		buffer = NULL;
		if (check_redir(tmp->args))
		{
			printf("redir\n");
			fill_rd(tmp, &buffer);
			ft_freearr(tmp->args);
			tmp->args = buffer;
		}
		else
			tmp->head = NULL;
		expand_files(data, tmp);
		tmp = tmp->next;
	}
}
