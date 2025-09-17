/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:30:24 by mdios-el          #+#    #+#             */
/*   Updated: 2025/07/11 20:30:29 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	d_size;
	size_t	s_size;

	d_size = ft_strlen(dst);
	s_size = ft_strlen(src);
	if (dstsize <= d_size)
		return (dstsize + s_size);
	i = d_size;
	j = 0;
	while ((i + j) < (dstsize - 1) && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (d_size + s_size);
}
