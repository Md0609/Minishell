/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:30:28 by mcombeau          #+#    #+#             */
/*   Updated: 2025/07/11 20:20:25 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(t_data *data, char **args)
{
	char	buf[PATH_MAX];
	char	*cwd;

	(void)args;
	if (data->working_dir)
	{
		ft_putendl_fd(data->working_dir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(buf, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	errmsg_cmd(MSG_PWD, NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
