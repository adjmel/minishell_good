#include "minishell.h"

t_redir	*rd_last_node(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_mini	*pc_last_node(t_mini *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	rd_addback(t_redir **head, t_redir *new)
{
	t_redir	*tmp;

	tmp = *head;
	if (!head || !new)
		return ;
	if (*head)
	{
		tmp = rd_last_node(tmp);
		tmp->next = new;
		new->previous = tmp;
	}
	else
		*head = new;
}

void	pc_addback(t_mini **head, t_mini *new)
{
	t_mini	*tmp;

	tmp = *head;
	if (!head || !new)
		return ;
	if (*head)
	{
		tmp = pc_last_node(tmp);
		tmp->next = new;
		new->previous = tmp;
	}
	else
		*head = new;
}
