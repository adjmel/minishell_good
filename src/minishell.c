/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:44:18 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/05 06:45:57 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	*name;
	t_data	data;


	init_session(&data, argc, argv, env);
	while (1)
	{
		name = prompt(&data);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		input = readline(name);
		free(name);
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
