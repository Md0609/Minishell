/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:27:54 by mdios-el          #+#    #+#             */
/*   Updated: 2025/07/11 20:28:05 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	start_check(t_data *data, int ac, char **av)
{
	(void)data;
	(void)av;
	if (ac != 1)
		return (usage_message(false));
	return (true);
}

void	minishell_start(t_data *data)
{
	int	parse_result;

	while (1)
	{
		set_signals_interactive();
		data->user_input = readline(PROMPT);
		set_signals_noninteractive();
		parse_result = parse_user_input(data);
		if (parse_result == 1)
			g_last_exit_code = execute(data);
		else if (parse_result == 0)
			g_last_exit_code = 0;
		else
			g_last_exit_code = 1;
		free_data(data, false);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (!start_check(&data, ac, av) || !init_data(&data, env))
		exit_shell(NULL, EXIT_FAILURE);
	minishell_start(&data);
	exit_shell(&data, g_last_exit_code);
	return (0);
}
