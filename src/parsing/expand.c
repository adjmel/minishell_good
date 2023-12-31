#include "minishell.h"

void	non_env_values(t_data *data, char *str, char **ptr)
{
	char	*tmp;

	if (*str == '?')
	{
		*ptr = ft_itoa(data->exit_status);
		tmp = *ptr;
		*ptr = ft_strjoin(*ptr, str + 1);
		free(tmp);
	}
	else if (!not_special(*str) && *str)
		*ptr = ft_strjoin("$", str);
	else
		*ptr = ft_strdup("");
}

char	*get_env_variable(t_data *data, char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	while (data->env[i])
	{
		ptr = ft_strstr(data->env[i], str);
		if (ptr)
		{
			if (*(ptr + ft_strlen(str)) == '=' && *str == *data->env[i])
			{
				ptr = ft_strdup(data->env[i] + (ft_strlen(str) + 1));
				free(str);
				return (ptr);
			}
		}
		i++;
	}
	non_env_values(data, str, &ptr);
	free(str);
	return (ptr);
}

void	get_env_value(t_data *data, char **buffer, char *str, int *i)
{
	char	*ptr1;
	char	*ptr2;
	int		j;

	(*i)++;
	j = *i;
	while (str[*i] && not_special(str[*i]))
		(*i)++;
	ptr1 = ft_substr(str, j, *i - j);
	ptr1 = get_env_variable(data, ptr1);
	if (!(*buffer))
		*buffer = ft_strdup("");
	ptr2 = *buffer;
	*buffer = ft_strjoin(*buffer, ptr1);
	free(ptr2);
	free(ptr1);
}

void	set_quotes(char *str, int i, int *key)
{
	if (str[i] == DOUBLE_QUOTE && *key != 3)
	{
		if (*key == 2) // ""
			*key = 1;
		else
			*key = 2;
	}
	else if (str[i] == SINGLE_QUOTE && *key != 2)
	{
		if (*key == 3) // ''
			*key = 1;
		else
			*key = 3;
	}
}

char	*expand(t_data *data, char *str, int quotes)
{
	int		key;
	char	*buffer;
	int		i;

	i = 0;
	key = 1;
	buffer = NULL;
	while (str[i])
	{
		if (quotes)
			set_quotes(str, i, &key);
		if (str[i] == '$' && str[i + 1] && key != 3)
			get_env_value(data, &buffer, str, &i);
		else
			buffer = str_concate(buffer, str[i++]);
	}	
	free(str);
	return (buffer);
}
