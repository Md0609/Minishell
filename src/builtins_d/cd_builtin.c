/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrillo <mgrillo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:19:13 by mdios-el          #+#    #+#             */
/*   Updated: 2025/07/17 15:28:03 by mgrillo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_wds(t_data *data, char *wd)
{
	set_env_var(data, "OLDPWD", get_env_var_value(data->env, "PWD"));
	set_env_var(data, "PWD", wd);
	if (data->old_working_dir)
	{
		free_ptr(data->old_working_dir);
		data->old_working_dir = ft_strdup(data->working_dir);
	}
	if (data->working_dir)
	{
		free_ptr(data->working_dir);
		data->working_dir = ft_strdup(wd);
	}
	free_ptr(wd);
}

/*
** Muestra un error formateado para cd usando strerror.
** Convierte el error ESTALE a ENOENT para mayor claridad.
*/
static	bool	chdir_errno_mod(char *path)
{
	if (errno == ESTALE)
		errno = ENOENT;
	errmsg_cmd(MSG_CD, path, strerror(errno), errno);
	return (false);
}

/*
** Realiza el cambio de directorio usando chdir.
** Actualiza las variables PWD y OLDPWD tras el cambio.
*/
static bool	change_dir(t_data *data, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (chdir_errno_mod(path));
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		errmsg_cmd(E_CD_ERROR_RETRIEVING,
			E_GETCWD_CANNOT_ACCESS,
			strerror(errno), errno);
		ret = ft_strjoin(data->working_dir, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		free_ptr(tmp);
	}
	else
		ret = ft_strdup(cwd);
	update_wds(data, ret);
	return (true);
}

/*
** Función principal del builtin 'cd' que gestiona sus argumentos.
** Maneja casos especiales como 'cd', 'cd -' y 'cd --' cd ~.
*/
int	cd_builtin(t_data *data, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0])
		|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = get_env_var_value(data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd(MSG_CD, NULL, E_HOME_NOT_SET, EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	if (args[2])
		return (errmsg_cmd(MSG_CD, NULL, E_TOO_MANY_ARGUMENTS, EXIT_FAILURE));
	if ((ft_strncmp(args[1], "-", 2) == 0)
		|| (ft_strncmp(args[1], "~", 2) == 0))
	{
		path = get_env_var_value(data->env, "OLDPWD");
		if (!path)
			return (errmsg_cmd(MSG_CD, NULL, E_OLDPWD_NOT_SET, EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	return (!change_dir(data, args[1]));
}
