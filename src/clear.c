#include "minishell.h"

void	clear_list(t_data *data)
{
	t_mini	*mini;
	t_redir	*rd_tmp;

	while (data->head)
	{
		mini = data->head;
		while (mini->head)
		{
			rd_tmp = mini->head;
			mini->head = mini->head->next;
			free(rd_tmp);
			rd_tmp = NULL;
		}
		data->head = data->head->next;
		free(mini);
		mini = NULL;
	}
}

void	clear(t_data *data)
{
	t_mini	*tmp1;
	t_redir	*tmp2;

	tmp1 = data->head;
	while (tmp1)
	{
		tmp2 = tmp1->head;
		while (tmp2)
		{
			free(tmp2->file);
			tmp2 = tmp2->next;
		}
		free(tmp1->cmd);
		if (tmp1->args)
			ft_freearr(tmp1->args);
		tmp1 = tmp1->next;
	}
	clear_list(data);
}
