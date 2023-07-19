#include "minishell.h"

char	**ft_tabdup(char **tab)
{
	char	**dup;
	int		i;

	dup = malloc(sizeof(char *) * (ft_tabsize(tab) + 1));
	if (!dup)
		exit(EXIT_FAILURE);
	i = 0;
	while (tab[i])
	{
		dup[i] = ft_strdup(tab[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
