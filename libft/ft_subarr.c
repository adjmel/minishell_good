#include "minishell.h"

char	**ft_subarr(char **tab, int start, int size)
{
	char	**arr;
	int		i;

	if (!tab)
		return (NULL);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
		arr[i++] = ft_strdup(tab[start++]);
	arr[i] = NULL;
	return (arr);
}
