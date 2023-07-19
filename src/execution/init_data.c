#include "minishell.h"

void	init_redirections(t_redir **redir)
{
	if (((*redir))->type == INPUT)
		((*redir))->fd = open(((*redir))->file, O_RDONLY, 0644);
	else if (((*redir))->type == OUTPUT)
		((*redir))->fd = open(((*redir))->file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (((*redir))->type == APPEND)
		((*redir))->fd = open(((*redir))->file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (((*redir))->type == HEREDOC)
		((*redir))->fd = -3;
	if (((*redir))->fd == -1 && access(((*redir))->file, F_OK) == -1)
		((*redir))->fd = -2;
}

static void	print_banner(void)
{
	printf(BLUE);
    printf("                                                                     \n");
    printf("                                                                     \n");
    printf("                                                                     \n");
	printf("███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██      \n");
    printf("████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██      \n");
    printf("██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██      \n");
    printf("██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██      \n");
    printf("██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████ \n");
    printf("                                                                     \n");
    printf("                                                                     \n");
	printf(ESC_COLOR);
}

void	init_data_and_banner(t_data *data, int argc, char **argv, char **env)
{
	(void) argc, (void) argv;
	ft_bzero(data, sizeof(t_data));
	init_bltn(data);
	data->env = ft_tabdup(env);
	print_banner();
}

void	dup_and_close(int fd, int new_fd)
{
	dup2(fd, new_fd);
	close(fd);
}
