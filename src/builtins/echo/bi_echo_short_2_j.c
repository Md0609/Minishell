
#include "minishell.h"

int	is_valid_arg(char *str)
{
	size_t	i;

	i = 1;
	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0' || str[i] == ' ')
		return (1);
	return (0);
}

size_t	check_more_n(t_input *in)
{
	size_t	i;
	size_t	start;

	i = 0;
	while (in->parsed && in->parsed[i])
	{
		start = i;
		if (in->parsed[i] != '-')
			return (start);
		i++;
		while (in->parsed[i] && in->parsed[i] == 'n' && in->parsed[i] != ' ')
			i++;
		if (in->parsed[i] != ' ' && in->parsed[i] != '\0')
			return (start);
		if (in->parsed[i])
			i++;
	}
	return (i);
}
