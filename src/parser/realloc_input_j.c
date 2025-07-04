
#include "minishell.h"

char	*ft_str_realloc(char *str, size_t num)
{
	char	*new;
	size_t	i;

	i = 0;
	new = (char *)ft_calloc(ft_strlen(str) + num + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	if (str)
		free(str);
	return (new);
}

void	dynamic_input(t_input *in, size_t k)
{
	if (in->token && k < in->realloc_counter * BUFFER)
		return ;
	else
	{
		in->realloc_counter++;
		in->token = ft_str_realloc(in->token, BUFFER);
		if (!in->token)
			clean_all(in, 1);
	}
}

void	dynamic_command(t_input *in, size_t k)
{
	if (in->command && k < in->realloc_counter * BUFFER)
		return ;
	else
	{
		in->realloc_counter++;
		in->command = ft_str_realloc(in->command, BUFFER);
		if (!in->command)
			clean_all(in, 1);
	}
}

void	dynamic_arg(t_input *in, size_t k)
{
	if (in->args && k < in->realloc_counter * BUFFER)
		return ;
	else
	{
		in->realloc_counter++;
		in->args = ft_str_realloc(in->args, BUFFER);
		if (!in->args)
			clean_all(in, 1);
	}
}
