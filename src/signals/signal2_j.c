
#include "minishell.h"

void	one_hundred_thirty(t_input *input)
{
	write(1, "\n", 1);
	input->last_exit_code = 130;
}

void	one_hundred_thirtyone(t_input *input)
{
	write(1, "Quit (core dumped)\n", 19);
	input->last_exit_code = 131;
}
