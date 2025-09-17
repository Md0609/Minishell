/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:22:47 by mdios-el          #+#    #+#             */
/*   Updated: 2025/07/11 20:22:48 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Comprueba si un token contiene '$' y le asigna el tipo VAR.
** Ignora la expansión para delimitadores de heredoc.
*/
static void	variable_check(t_token **token_node)
{
	int	i;

	i = 0;
	while ((*token_node)->str[i])
	{
		if ((*token_node)->str[i] == '$')
		{
			if ((*token_node)->prev && (*token_node)->prev->type == HEREDOC)
				break ;
			(*token_node)->type = VAR;
			return ;
		}
		i++;
	}
}

/*
** Recorre la lista de tokens para identificar los que tienen variables.
** También valida la sintaxis de operadores consecutivos.
*/
int	check_if_var(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	if (temp->type == PIPE)
	{
		errmsg(E_SYNTAX_ERROR_NEAR, temp->str, true);
		return (FAILURE);
	}
	while (temp)
	{
		variable_check(&temp);
		if (check_consecutives(&temp) == FAILURE)
			return (FAILURE);
		temp = temp->next;
	}
	return (SUCCESS);
}
