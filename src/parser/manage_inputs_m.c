
#include "minishell.h"

void	ft_manage_input(t_input *input)
{
	if (handle_redirection(input) == 1)
		return ;
	if (ft_strcmp(input->command, "pwd") == 0)
		ft_pwd(input->args, input);
	else if (ft_strcmp(input->command, "cd") == 0)
		ft_cd(input);
	else if (ft_strcmp(input->command, "echo") == 0)
		echo_short(input, input->outputfd);
	else if (ft_strcmp(input->command, "export") == 0)
		ft_export(input, &input->envp);
	else if (ft_strcmp(input->command, "env") == 0)
		ft_env(input, input->envp);
	else if (ft_strcmp(input->command, "unset") == 0)
		ft_unset(input);
	else if (ft_strcmp(input->command, "exit") == 0)
		ft_exit(input);
	else if (!(ft_strcmp(input->command, "") == 0 || input->command == NULL))
		execute_command(input);
	else if (input->input_split && input->input_split[0]
		&& !input->input_split[0][0])
	{
		ft_printf("minishell: %s: command not found\n", input->input_split[0]);
		input->last_exit_code = 127;
	}
	input->last_dollar_ = ft_last_str(input, input->split_exp);
}
