#include "minishell.h"

t_redir	*rd_new_node(char *file, int type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file = ft_strdup(file);
	new->fd = -1;
	new->type = type;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

t_mini	*pc_new_node(char **args, int sep, int lvl)
{
	t_mini	*new;

	new = malloc(sizeof(t_mini));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->args = args;
	new->separator = sep;
	new->error = 0;
	new->level = lvl;
	new->head = NULL;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}
