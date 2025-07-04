
#include "minishell.h"

void	clean_all(t_input *input, int error)
{
	ft_manage_history(NULL, 1);
	ft_input_free(input);
	if (error)
		rl_clear_history();
	if (error)
		exit(error);
}
