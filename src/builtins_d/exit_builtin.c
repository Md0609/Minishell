/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:20:08 by mdios-el          #+#    #+#             */
/*   Updated: 2025/07/11 20:20:09 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX)
		|| (neg == -1 && num > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

static int	ft_atoi_long(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (check_out_of_range(neg, num, error))
			break ;
		i++;
	}
	return (num * neg);
}

/*
** Convierte y valida el argumento numérico de exit.
** Devuelve el código de salida como un entero (0-255).
*/
static int	get_exit_code(char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (g_last_exit_code);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return (i % 256);
}

/*
** Comprueba si exit se ejecuta en un pipeline.
** Suprime el mensaje "exit" si hay más de un comando.
*/
static bool	is_quiet_mode(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	if (!cmd)
		return (false);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (true);
	return (false);
}

/*
** Función principal del builtin 'exit', que termina la minishell.
** Gestiona el código de salida y los errores de argumentos.
*/
int	exit_builtin(t_data *data, char **args)
{
	int		exit_code;
	bool	error;
	bool	quiet;

	quiet = is_quiet_mode(data);
	error = false;
	if (!quiet)
		ft_putendl_fd(MSG_EXIT, 2);
	if (!args || !args[1])
		exit_code = g_last_exit_code;
	else
	{
		exit_code = get_exit_code(args[1], &error);
		if (error)
			exit_code = errmsg_cmd(MSG_EXIT, args[1],
					"numeric argument required", 2);
		else if (args[2])
			return (errmsg_cmd(MSG_EXIT, NULL, E_TOO_MANY_ARGUMENTS, 1));
	}
	exit_shell(data, exit_code);
	return (2);
}
