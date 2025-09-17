/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:23:36 by mdios-el          #+#    #+#             */
/*   Updated: 2025/07/11 20:23:40 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenization(t_data *data, char *str)
{
	int	i;
	int	end;
	int	start;
	int	status;

	i = -1;
	start = 0;
	end = ft_strlen(str);
	status = DEFAULT;
	while (++i <= end)
	{
		status = set_status(status, str, i);
		if (status == DEFAULT)
			start = save_word_or_sep(&i, str, start, data);
	}
	if (status != DEFAULT)
	{
		if (status == DQUOTE)
			errmsg(E_UNEXPECTED_EOF_MATCHING, "\"", true);
		else if (status == SQUOTE)
			errmsg(E_UNEXPECTED_EOF_MATCHING, "'", true);
		errmsg(E_SYNTAX_ERROR, E_UNEXPECTED_EOF, false);
		return (1);
	}
	return (0);
}
