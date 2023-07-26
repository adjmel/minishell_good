#include "minishell.h"

int	executor(t_data *data, t_mini *mini, int _pipe[2], int prev_pipe[2])
{
	pid_t	pid;
	int		status;

	if (!mini->cmd)
	{
		close(_pipe[1]);
		close(prev_pipe[0]);
		return (127);
	}
	if (mini->cmd[0] == '\0')
		return (exec_empty_cmd(mini));
	if (is_builtin(mini->cmd))
		return (exec_builtin_cmd(data, mini, _pipe, prev_pipe));
	status = 0;
	pid = fork();
	if (pid == 0)
		exec_cmd(data, mini, _pipe, prev_pipe);
	else if (pid > 0)
		wait_for_child(pid, _pipe, prev_pipe, &status);
	else
		fd_printf(2, FAIL_FORK, strerror(errno));
	return (exit_status(status));
}


void	inspector(t_data *data)
{
	t_inspector	s;

	error_command(data);
	s.i = -1; //
	s.current = data->head;
	while (s.current)
	{
		error_dots(data, &s.current);
		error_dir(data, &s.current);
		init_exec(data, s.current, s._pipe, s.prev_pipe, s.i);
		level_priority(data, &s.current, &s.level);
		s.i++;
		if (s.current->separator != PIPE_TOKEN)
			s.i = -1;
		s.current = s.current->next;
	}
	close(s._pipe[0]);
	close(s._pipe[1]);
	close(s.prev_pipe[0]);
	close(s.prev_pipe[1]);
	close_heredocs(data);
}

void	execution(t_data *data)
{
	t_supervisor	s;

	s.mn = data->head;
	while (s.mn)
	{
		if (s.mn->head)
		{
			s.rd = s.mn->head;
			while (s.rd)
			{
				if (s.rd->type == HEREDOC
					&& heredoc_and_errors(data, &s.rd, &s.status, &s.pid))
					return ;
				else if (s.rd->type == INPUT && (!s.mn->cmd || !(*s.mn->cmd))
					&& !s.mn->error && access(s.rd->file, F_OK) == -1)
				{
					s.mn->error = 1;
					fd_printf(2, CUSTOM, s.rd->file, strerror(errno));
				}
				s.rd = s.rd->next;
			}
		}
		s.mn = s.mn->next;
	}
	inspector(data);
}
