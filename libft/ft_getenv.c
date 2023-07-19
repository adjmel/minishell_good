#include "minishell.h"

char	*ft_getenv(t_data *data, char *str)
{
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], str, ft_strlen(str))
			&& data->env[i][ft_strlen(str)] == '=')
		{
			value = ft_strdup(data->env[i] + ft_strlen(str) + 1);
			break ;
		}
		i++;
	}
	return (value);
}
