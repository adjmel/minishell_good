#include "minishell.h"

int	exec_builtin_pipe(t_data *data, t_mini *mini, int _pipe[2], int prev_pipe[2])
{
	pid_t	pid;
	int		status;
	(void)data;

	status = 0;
	pid = fork();
	if (pid == 0)
		exec_piped(data, mini, _pipe, prev_pipe);
	else if (pid > 0)
		wait_for_child(pid, _pipe, prev_pipe, &status);
	else
		fd_printf(2, FAIL_FORK, strerror(errno));
	return (exit_status(status));
}

void	exec_piped(t_data *data, t_mini *mini, int _pipe[2], int prev_pipe[2])
{
	t_redir	*current;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (mini->previous && mini->previous->separator == PIPE_TOKEN)
		dup_and_close(prev_pipe[0], STDIN_FILENO);
	if (mini->separator == PIPE_TOKEN)
		dup_and_close(_pipe[1], STDOUT_FILENO);
	current = mini->head;
	while (current)
	{
		dup_or_error(current);
		current = current->next;
	}
	exit(exec_builtin(data, mini->cmd, mini->args));
}

void	error_dots(t_data *data, t_mini **mini)
{
	if (!(*mini)->args)
		return ;
	if (!ft_strcmp((*mini)->args[0], "."))
	{
		fd_printf(STDERR_FILENO, "minishell: .: filename argument required\n");
		fd_printf(STDERR_FILENO, ".: usage: . filename [arguments]\n");
		data->exit_status = 2;
		(*mini)->error = 1;
	}
	else if (!ft_strcmp((*mini)->args[0], ".."))
	{
		fd_printf(STDERR_FILENO, ERR_CMD_NOT_FOUND, (*mini)->args[0]);
		data->exit_status = 127;
		(*mini)->error = 1;
	}
}

void	error_dir(t_data *data, t_mini **mini)
{
	DIR	*dir;

	if(!(*mini)->cmd)
		return;
	else
		dir = opendir((*mini)->cmd);
	if (dir && !(*mini)->error)
	{
		fd_printf(2, CUSTOM, (*mini)->args[0], "is a directory");
		(*mini)->error = 1;
		data->exit_status = 126;
		closedir(dir);
	}
}

int	is_path(t_data *data)
{
	int	i;

	if (!data->env)
		return (0);
	i = -1;
	while (data->env[++i])
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
			return (1);
	return (0);
}