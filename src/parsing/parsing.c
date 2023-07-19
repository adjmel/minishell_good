#include "minishell.h"

int	not_metachar(char c)
{
	if (c != RIGHT_ARROW && c != LEFT_ARROW
		&& c != PIPE && c != SPACE && c != TAB
		&& c != AMPERSAND && c != OPEN_PARENTHESE
		&& c != CLOSE_PARENTHESE)
		return (1);
	return (0);
}

void	space_skiper(char *str, int *i)
{
	while (str[*i] == SPACE || str[*i] == TAB)
		(*i)++;
}

int	empty(t_data *data, char *input)
{
	int	i;

	i = -1;
	if (!input)
	{
		printf("exit\n");
		exit(data->exit_status);
	}
	while (input[++i])
		if (input[i] != SPACE && input[i] != TAB)
			return (0);
	free(input);
	return (1);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	parsing(t_data *data, char *input)
{
	char	**commands;

	data->errors = 0;
	commands = lexical_analysis(input);
	if (syntax_error(data, commands))
	{
		data->errors = 1;
		free(input);
		ft_freearr(commands);
		return ;
	}
	parser(data, commands);
	ft_freearr(commands);
	free(input);
}
