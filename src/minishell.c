#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	data;

	init_data_and_banner(&data, argc, argv, env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		input = readline("\033[1;34m minishell> \033[0m");
		if (empty(&data, input))
			continue ;
		add_history(input);
		parsing(&data, input);
		if (data.errors)
			continue ;
		if (DEBUG)
			printf_struct(&data);
		supervisor(&data);
		clear(&data);
	}
}
