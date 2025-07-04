
#include "minishell.h"

void	do_even_token_dollars2(t_input *in, size_t w, size_t *i, size_t *k)
{
	in->spaced = 1;
	while (in->input_split[w][*i] && in->input_split[w][*i] != '?')
		in->token[(*k)++] = in->input_split[w][(*i)++];
}

void	token_env_question2(t_input *in, size_t w, size_t *i, size_t *k)
{
	while (in->input_split[w][*i] && in->input_split[w][*i] != '$')
	{
		dynamic_input(in, *k);
		in->token[(*k)++] = in->input_split[w][(*i)++];
	}
}

void	token_env_if_even_dollars2(t_input *in, size_t w, size_t *i, size_t *k)
{
	while (in->input_split[w][*i] && in->input_split[w][(*i) + 1] != ' ')
	{
		(*i)++;
		dynamic_input(in, *k);
		in->token[(*k)++] = in->input_split[w][(*i)];
	}
}

void	token_rare_cases2(t_input *in, size_t *k, char *str, size_t id)
{
	in->token[(*k)++] = '$';
	dynamic_input(in, *k);
	in->token[(*k)++] = str[id];
}
