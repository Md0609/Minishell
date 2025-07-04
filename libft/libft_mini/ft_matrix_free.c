/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:09:14 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/30 00:09:53 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_matrix_free(char ***matrix)
{
	int	i;

	i = 0;
	if (!matrix || !*matrix)
		return ;
	while ((*matrix)[i])
	{
		if ((*matrix)[i])
			free((*matrix)[i]);
		(*matrix)[i] = NULL;
		i++;
	}
	free((*matrix));
	*matrix = NULL;
}
