
#include "minishell.h"

void	do_even_token_dollars(t_input *in, size_t w, size_t *i, size_t *k)
{
	size_t	j;

	j = 0;
	while (in->input_split[w][*i] && in->input_split[w][(*i) + 1] != ' '
		&& in->input_split[w][*i] != '$' && in->env_n != -2)
	{
		if (is_quoted(in, w) == 2 && in->input_split[w][*i] == '\'')
		{
			if (*i > 0)
				(*i)--;
			return ;
		}
		dynamic_input(in, *k);
		if (in->dollars > 0 && (in->dollars % 2) && (j < in->env_len))
			in->token[(*k)++] = in->input_split[w][(*i)];
		else if (j >= in->env_len
			&& !ft_isdigit(in->input_split[w][in->idollar])
			&& !ft_strrchr(D_Y_ODDCHAR, in->input_split[w][in->idollar])
			&& !ft_strrchr(N_ODDCHAR, in->input_split[w][in->idollar]))
			do_even_token_dollars2(in, w, i, k);
		if (in->input_split[w][*i] && in->input_split[w][*i] != '?')
			(*i)++;
		j++;
	}
}

void	token_env_question(t_input *in, size_t w, size_t *i, size_t *k)
{
	char	*number;
	size_t	l;

	l = 0;
	(*i)++;
	if (!(in->dollars % 2))
	{
		number = ft_itoa(in->last_exit_code);
		if (!number)
			clean_all(in, 1);
		while (number[l])
		{
			dynamic_input(in, *k);
			in->token[(*k)++] = number[l++];
		}
		free(number);
	}
	else
	{
		dynamic_input(in, *k);
		in->token[(*k)++] = '?';
	}
	token_env_question2(in, w, i, k);
}

void	token_invalid_envs(t_input *in, size_t w, size_t *i, size_t *k)
{
	if (in->env_n > -1)
		in->env_len = validlen_env(in->envp[in->env_n], '=');
	else if (in->env_n == -1)
		in->env_len = invalidlen_env(in->input_split[w] + (*i));
	do_even_token_dollars(in, w, i, k);
	if (in->env_n < 0
		&& (ft_isalpha(in->input_split[w][in->idollar])
		|| in->input_split[w][in->idollar] == '_'))
		token_rest_no_env(in, w, i, k);
	else if (in->env_n == -1)
		token_rare_cases(in, w, i, k);
	else if (in->env_n == -2)
		token_env_question(in, w, i, k);
}

void	save_if_spaced_valid_env(t_input *in, size_t w)
{
	size_t	i;
	int		env_n;
	size_t	idollar;

	i = 0;
	in->dollars = 0;
	while (in->input_split[w][i] != '$')
		i++;
	idollar = i;
	while (in->input_split[w][i] == '$')
	{
		(in->dollars)++;
		i++;
	}
	env_n = valid_env((in->input_split[w] + i), in, w);
	if (env_n == -1
		&& (ft_isalpha(in->input_split[w][i]) || in->input_split[w][i] == '_')
		&& !idollar
		&& is_quoted(in, w) != 2 && in->dollars == 1)
		space_after_first_invalid_env(in, w, i, 0);
}

void	expand_token_dollar(t_input *in, size_t *i, size_t *j, size_t *k)
{
	save_if_spaced_valid_env(in, *i);
	in->dollars = 0;
	while (in->input_split[*i][*j])
	{
		if (in->input_split[*i][*j] != '$')
		{
			dynamic_input(in, *k);
			in->token[(*k)++] = in->input_split[*i][(*j)];
		}
		else
		{
			while (in->input_split[*i][(*j) + 1] == '$')
			{
				(*j)++;
				(in->dollars)++;
			}
			in->idollar = (*j) + 1;
			token_valid_env_variable(in, *i, j, k);
			token_invalid_envs(in, *i, j, k);
		}
		if (in->input_split[*i][*j] && in->input_split[*i][*j] != '$')
			(*j)++;
	}
}
