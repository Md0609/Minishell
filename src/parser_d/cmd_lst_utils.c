/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:23:53 by mdios-el          #+#    #+#             */
/*   Updated: 2025/07/11 20:23:54 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Inicializa a NULL o false los campos de un nuevo t_command.
** Asegura que no haya valores basura al crear un nodo.
*/
static void	initialize_cmd(t_command **cmd)
{
	(*cmd)->command = NULL;
	(*cmd)->path = NULL;
	(*cmd)->args = NULL;
	(*cmd)->pipe_output = false;
	(*cmd)->pipe_fd = 0;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}

/*
** Crea y reserva memoria para un nuevo nodo t_command.
** Inicializa sus valores por defecto con initialize_cmd.
*/
t_command	*lst_new_cmd(bool value)
{
	t_command	*new_node;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!(new_node))
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_command));
	new_node->pipe_output = value;
	initialize_cmd(&new_node);
	return (new_node);
}

/*
** Añade un nuevo nodo de comando al final de la lista.
** Maneja el caso en que la lista esté vacía.
*/
void	lst_add_back_cmd(t_command **alst, t_command *new_node)
{
	t_command	*start;

	start = *alst;
	if (start == NULL)
	{
		*alst = new_node;
		return ;
	}
	if (alst && *alst && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

/*
** Devuelve un puntero al último nodo de la lista de comandos.
** Permite acceder rápidamente al final de la lista.
*/
t_command	*lst_last_cmd(t_command *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}
