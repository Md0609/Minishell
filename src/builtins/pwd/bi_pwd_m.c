
#include "minishell.h"

void	ft_pwd(char *args, t_input *input)
{
	char	cwd[1024];
	int		len;

	len = ft_strlen(args);
	if ((args[0] == '-' && args[1] != '-' && args[1])
		|| (args[0] == '-' && args[1] == '-' && len > 2))
	{
		printf("pwd: usage: pwd\n");
		input->last_exit_code = 1;
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		input->last_exit_code = 0;
	}
	else
	{
		perror("minishell: pwd");
		input->last_exit_code = 1;
	}
}
