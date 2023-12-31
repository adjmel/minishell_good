#include "minishell.h"

void	quote_analyse(char **buffer, char *input, int *i)
{
	int		s_quote;
	int		d_quote;

	s_quote = 0;
	d_quote = 0;
	*buffer = str_concate(*buffer, input[*i]);
	if (input[(*i)++] == SINGLE_QUOTE)
		s_quote++;
	else
		d_quote++;
	while (input[*i])
	{
		if (input[*i] == SINGLE_QUOTE && d_quote % 2 == 0)
			s_quote++;
		else if (input[*i] == DOUBLE_QUOTE && s_quote % 2 == 0)
			d_quote++;
		*buffer = str_concate(*buffer, input[(*i)++]);
		if (s_quote % 2 == 0 && d_quote % 2 == 0
			&& (!not_metachar(input[*i]) || !input[(*i)]))
			break ;
		/*if (s_quote % 2 == 0 && d_quote % 2 == 0
			&& (!not_metachar(input[*i + 1]) || !input[(*i) + 1]))
			break ;
		*buffer = str_concate(*buffer, input[(*i)++]);*/
	}
	/*if (input[*i])
		*buffer = str_concate(*buffer, input[(*i)++]);*/
}

void	separator_analyse(char **buffer, char *input, int *i)
{
	*buffer = str_concate(*buffer, input[*i]);
	if (input[(*i) + 1] == input[*i])
		*buffer = str_concate(*buffer, input[++(*i)]);
	(*i)++;
}

void	words_analyse(char **buffer, char *input, int *i)
{
	while (input[*i])
	{
		*buffer = str_concate(*buffer, input[(*i)++]);
		if (input[*i] == SINGLE_QUOTE || input[*i] == DOUBLE_QUOTE)
			quote_analyse(buffer, input, i);
		if (!not_metachar(input[*i]))
			break ;
	}
}

char	**lexical_analysis(char *input)
{
	char	**commands;
	char	*buffer;
	int		i;

	commands = NULL;
	buffer = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == SPACE || input[i] == TAB)
			space_skiper(input, &i);
		else if (input[i] == SINGLE_QUOTE || input[i] == DOUBLE_QUOTE)
			quote_analyse(&buffer, input, &i);
		else if (input[i] == PIPE || input[i] == AMPERSAND
			|| input[i] == RIGHT_ARROW || input[i] == LEFT_ARROW)
			separator_analyse(&buffer, input, &i);
		else if (input[i] == OPEN_PARENTHESE || input[i] == CLOSE_PARENTHESE)
			buffer = str_concate(buffer, input[i++]);
		else
			words_analyse(&buffer, input, &i);
		if (buffer)
			commands = arr_concate(commands, buffer);
		buffer_reset(&buffer);
	}
	return (commands);
}
