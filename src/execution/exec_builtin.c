#include "minishell.h"

void	init_bltn(t_data *data)
{
	data->builtins[0].name = "echo";
	data->builtins[0].func = &re_echo;
	data->builtins[1].name = "cd";
	data->builtins[1].func = &re_cd;
	data->builtins[2].name = "pwd";
	data->builtins[2].func = &re_pwd;
	data->builtins[3].name = "export";
	data->builtins[3].func = &re_export;
	data->builtins[4].name = "unset";
	data->builtins[4].func = &re_unset;
	data->builtins[5].name = "env";
	data->builtins[5].func = &re_env;
	data->builtins[6].name = "exit";
	data->builtins[6].func = &re_exit;
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	exec_builtin(t_data *data, char *cmd, char **args)
{
	int	i;

	i = -1;
	data->exit_status = 0;
	while (++i < 7)
	{
		if (ft_strcmp(cmd, data->builtins[i].name) == 0)
		{
			data->builtins[i].func(args, data);
			return (data->exit_status);
		}
	}
	return (1);
}

int	dup_or_error_builtin(t_redir *current)
{
	init_redirections(&current);
	if (current->fd == -1)
		return (fd_printf(2, ERR_PERMISSION, current->file),
			EXIT_FAILURE);
	if (current->fd == -2)
		return (fd_printf(2, ERR_NO_SUCH_FILE, current->file),
			EXIT_FAILURE);
	if (current->type == INPUT)
		dup_and_close(current->fd, STDIN_FILENO);
	else if (current->type == OUTPUT || current->type == APPEND)
		dup_and_close(current->fd, STDOUT_FILENO);
	else if (current->type == HEREDOC)
	{
		current->fd = open(HERE_DOC, O_RDONLY, 0644);
		dup_and_close(current->fd, STDIN_FILENO);
	}
	return (EXIT_SUCCESS);
}

int	exec_builtin_cmd(t_data *data, t_mini *proc, int _pipe[2], int prev_pipe[2])
{
	t_exec_builtin	s;

	if ((proc->previous && proc->previous->separator == PIPE_TOKEN)
		|| proc->separator == PIPE_TOKEN)
		return (exec_builtin_pipe(data, proc, _pipe, prev_pipe));
	s.pipe_stdin = dup(STDIN_FILENO);
	s.pipe_stdout = dup(STDOUT_FILENO);
	if (proc->previous && proc->previous->separator == PIPE_TOKEN)
		dup_and_close(prev_pipe[0], 0);
	if (proc->separator == PIPE_TOKEN)
		dup_and_close(_pipe[1], 1);
	s.current = proc->head;
	while (s.current)
	{
		if (dup_or_error_builtin(s.current) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		s.current = s.current->next;
	}
	s.status = exec_builtin(data, proc->cmd, proc->args);
	dup_and_close(s.pipe_stdout, STDOUT_FILENO);
	dup_and_close(s.pipe_stdin, STDIN_FILENO);
	return (s.status);
}
