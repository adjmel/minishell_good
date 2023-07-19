#include "minishell.h"

t_redir	*rd_last_node(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_proc	*pc_last_node(t_proc *lst)
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

void	pc_addback(t_proc **head, t_proc *new)
{
	t_proc	*tmp;

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
