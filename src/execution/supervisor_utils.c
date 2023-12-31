#include "minishell.h"

void	init_exec(t_data *data, t_mini *proc, int prev_pipe[2], int _pipe[2],
		int i)
{
	if (i % 2)
	{
		if (pipe(prev_pipe) == -1)
		{
			fd_printf(STDERR_FILENO, FAIL_PIPE, strerror(errno));
			exit(EXIT_FAILURE);
		}
		data->exit_status = executor(data, proc, prev_pipe, _pipe);
	}
	else
	{
		if (pipe(_pipe) == -1)
		{
			fd_printf(STDERR_FILENO, FAIL_PIPE, strerror(errno));
			exit(EXIT_FAILURE);
		}
		data->exit_status = executor(data, proc, _pipe, prev_pipe);
	}
}

int	priority_condition(t_mini *proc, int level, int token)
{
	if (token == AND_TOKEN)
		return (proc && (proc->separator == AND_TOKEN
				|| proc->separator == PIPE_TOKEN) && proc->level >= level);
	else if (token == OR_TOKEN)
		return (proc && ((proc->separator == OR_TOKEN
					|| proc->separator == PIPE_TOKEN)
				|| (proc->separator == AND_TOKEN
					&& proc->level > level)) && proc->level >= level);
	return (EXIT_SUCCESS);
}

void	level_priority(t_data *data, t_mini **proc, int *level)
{
	if (data->exit_status && (*proc)->separator == AND_TOKEN)
	{
		*level = (*proc)->level;
		while (priority_condition(*proc, *level, AND_TOKEN))
			*proc = (*proc)->next;
	}
	else if (data->exit_status == 0 && (*proc)->separator == OR_TOKEN)
	{
		*level = (*proc)->level;
		while (priority_condition(*proc, *level, OR_TOKEN))
		{
			if ((*proc)->separator == AND_TOKEN)
				*level = (*proc)->level;
			*proc = (*proc)->next;
		}
	}
}

int	heredoc_and_errors(t_data *data, t_redir **redir, int *status, pid_t *pid)
{
	*pid = fork();
	if (*pid == 0)
		exec_heredoc(data, *redir);
	else if (*pid > 0)
	{
		if (handle_heredoc(data, *pid, status))
			return (EXIT_FAILURE);
	}
	else
		fd_printf(STDERR_FILENO, FAIL_FORK, strerror(errno));
	return (EXIT_SUCCESS);
}

void	error_command(t_data *data)
{
	t_mini	*current;

	current = data->head;
	while (current)
	{
		if (!current->cmd && !(current->head && current->head->type == INPUT)
			&& !current->error)
		{
			if (ft_strchr(current->args[0], '/'))
				fd_printf(2, ERR_NO_SUCH_FILE, current->args[0]);
			else if (!is_path(data))
				fd_printf(2, ERR_NO_SUCH_FILE, current->args[0]);
			else
				fd_printf(2, ERR_CMD_NOT_FOUND, current->args[0]);
		}
		current = current->next;
	}
}
