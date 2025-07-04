
#include "minishell.h"

void	assign_token_status(t_input *input, t_split *sq, char letter)
{
	if (is_spaced(sq, sq->start))
	{
		(void)letter;
		if (sq->c == '"')
			input->spaced = DQUO_SP;
		else if (sq->c == '\'')
			input->spaced = SQUO_SP;
		else if (sq->c == ' ')
			input->spaced = EPTY_SP;
	}
	else
	{
		if (sq->c == '"')
			input->spaced = DQUO_NSP;
		else if (sq->c == '\'')
			input->spaced = SQUO_NSP;
		else if (sq->c == ' ')
			input->spaced = EPTY_NSP;
	}
}

