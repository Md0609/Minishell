
#include "minishell.h"

void	ft_manage_history(char *input, bool clean)
{
	static char	*last_input = NULL;

	if (clean)
	{
		if (last_input)
			free(last_input);
		return ;
	}
	if (!input[1] || !(*input))
		return ;
	if (!last_input || ft_strcmp(last_input, input) != 0)
	{
		add_history(input);
		if (last_input)
			free (last_input);
		last_input = ft_strdup(input);
	}
}
