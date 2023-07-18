/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:51:43 by absalhi           #+#    #+#             */
/*   Updated: 2023/02/01 23:11:15 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_args(char **args, int tab)
{
	int	i;

	i = -1;
	if (!args)
		return ;
	while (args[++i])
		printf("%*c     .args[%d] = %s\n", tab, ' ', i, args[i]);
}

void	printf_redir(t_redir *redir, int tab)
{
	t_redir	*current;

	current = redir;
	while (current)
	{
		printf("\n%*c     .redir->type = %d\n", tab, ' ', current->type);
		printf("%*c     .redir->fd = %d\n", tab, ' ', current->fd);
		printf("%*c     .redir->file = %s\n", tab, ' ', current->file);
		printf("%*c     .redir->next = %p\n\n", tab, ' ', current->next);
		current = current->next;
	}
}

void	printf_first_element(t_data *data)
{
	printf("t_data g_data = {\n\n");
	printf("   .errors = %d\n", data->errors);
	printf("   .exit_status = %d\n\n", data->exit_status);
	printf("   .head = %p\n", data->head);
	printf("     .head->cmd = %s\n", data->head->cmd);
	printf("     .head->args = %p\n", data->head->args);
	printf_args(data->head->args, 0);
	printf("     .head->separator = %d\n", data->head->separator);
	printf("     .head->redir = %p\n", data->head->head);
	printf_redir(data->head->head, 0);
	printf("     .head->level = %d\n", data->head->level);
	printf("     .head->next = %p\n\n", data->head->next);
}

void	printf_struct(t_data *data)
{
	int		i;
	t_proc	*current;

	printf_first_element(data);
	i = 0;
	current = data->head->next;
	while (current)
	{
		printf("%*c   .current = %p\n", i, ' ', current);
		printf("%*c     .current->cmd = %s\n", i, ' ', current->cmd);
		printf("%*c     .current->args = %p\n", i, ' ', current->args);
		printf_args(current->args, i);
		printf("%*c     .current->separator = %d\n", i, ' ', current->separator);
		printf("%*c	    .current->redir = %p\n", i, ' ', current->head);
		printf_redir(current->head, i);
		printf("%*c     .current->level = %d\n", i, ' ', current->level);
		printf("%*c     .current->next = %p\n\n", i, ' ', current->next);
		current = current->next;
		i++;
	}
	printf("};\n");
}
