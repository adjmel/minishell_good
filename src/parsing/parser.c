#include "minishell.h"

void	get_cmd_path(t_data *data)
{
	t_proc	*tmp;

	tmp = data->head;
	while (tmp)
	{
		if (!tmp->args)
			tmp->cmd = ft_strdup("");
		else
			tmp->cmd = absolute_path(data, tmp->args[0]);
		tmp = tmp->next;
	}
}

char	*del_quote(char *str)
{
	char	*buffer;
	char	quote;
	int		i;

	i = 0;
	buffer = NULL;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
		{
			quote = str[i++];
			while (str[i] != quote)
				buffer = str_concate(buffer, str[i++]);
			i++;
		}
		if (str[i] && str[i] != SINGLE_QUOTE && str[i] != DOUBLE_QUOTE)
			buffer = str_concate(buffer, str[i++]);
	}
	if (!buffer)
		buffer = ft_strdup("");
	free(str);
	return (buffer);
}

void	quote_expand(t_data *data, t_proc *proc)
{
	int		i;

	i = 0;
	while (proc->args && proc->args[i])
	{
		proc->args[i] = expand(data, proc->args[i], 1);
		if (ft_strchr(proc->args[i], '\'') || ft_strchr(proc->args[i], '"'))
			proc->args[i] = del_quote(proc->args[i]);
		i++;
	}
}

void	parser(t_data *data, char **lx)
{
	t_proc	*tmp;

	init_list(data, lx);
	init_rd(data);
	tmp = data->head;
	while (tmp)
	{
		wildcard(tmp);
		quote_expand(data, tmp);
		tmp = tmp->next;
	}
	get_cmd_path(data);
}