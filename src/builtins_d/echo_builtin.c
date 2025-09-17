/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:19:33 by mdios-el          #+#    #+#             */
/*   Updated: 2025/07/11 20:19:39 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Comprueba si un argumento es una flag -n válida (ej: -n, -nnn).
** Devuelve true si es una flag -n, y false en caso contrario.
*/
static bool	is_n_flag(char *arg)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 0;
	if (arg[i] != '-')
		return (n_flag);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		n_flag = true;
	return (n_flag);
}

/*
** Imprime los argumentos de echo desde un índice dado.
** Gestiona los espacios y el salto de línea final (si no hay flag -n).
*/
static void	echo_print_args(char **args, bool n_flag, int i)
{
	if (!args[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

/*
** Función principal del builtin 'echo'.
** Imprime argumentos, gestionando la flag -n para omitir el salto de línea.
*/
int	echo_builtin(t_data *data, char **args)
{
	int		i;
	bool	n_flag;

	(void)data;
	n_flag = false;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	echo_print_args(args, n_flag, i);
	return (EXIT_SUCCESS);
}
