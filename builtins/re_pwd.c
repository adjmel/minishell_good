#include "minishell.h"

void	ft_chdir(t_data *data, char *path)
{
	int	i;

	set_oldpwd(data);
	i = chdir(path);
	if (i)
	{
		ft_dprintf(STDERR_FILENO, ERR_NO_SUCH_FILE_2, "cd", path);
		data->exit_status = EXIT_FAILURE;
		return ;
	}
	printf("%s\n", path);
	set_pwd(data);
	free(path);
}

void	cd_oldpwd(t_data *data)
{
	char	*path;

	path = ft_getenv(data, "OLDPWD");
	if (!path)
	{
		ft_dprintf(STDERR_FILENO, ERR_UNSET, "OLDPWD");
		data->exit_status = EXIT_FAILURE;
	}
	else
		ft_chdir(data, path);
}

void	re_pwd(char **args, t_data *data)
{
	char	*pwd;
	(void)data;

	(void) args;
	pwd = getcwd(NULL, 0);
	if (pwd)
		printf("%s\n", pwd);
	else
		pwd = ft_getenv(data, "OLDPWD");
	free(pwd);
}
