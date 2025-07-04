
#include "minishell.h"

static char	*get_username(void)
{
	char	*username;

	username = getenv("USER");
	if (!username)
		username = "user";
	return (username);
}

static void	get_short_hostname(char *hostname, size_t size)
{
	if (gethostname(hostname, size) != 0)
		ft_strlcpy(hostname, "localhost", size);
	else
	{
		char *dot = ft_strchr(hostname, '.');
		if (dot)
			*dot = '\0';
	}
}

static char	*get_current_working_dir(void)
{
	char	*cwd;
	char	*home;
	char	*temp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("?"));
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		temp = ft_strjoin("~", cwd + ft_strlen(home));
		free(cwd);
		cwd = temp;
	}
	return (cwd);
}

static char	*build_prompt_string(const char *username, const char *hostname, const char *cwd)
{
	char	*prompt;
	char	*temp;

	prompt = ft_strjoin("\001\033[1;32m\002", username);
	temp = ft_strjoin(prompt, "@");
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, hostname);
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, ":");
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, cwd);
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, "\001\033[0m\002$ ");
	free(prompt);
	return (temp);
}

char	*get_prompt(t_input *input)
{
	char	hostname[1024];
	char	*cwd;
	char	*prompt;

	(void)input;
	get_short_hostname(hostname, sizeof(hostname));
	cwd = get_current_working_dir();
	prompt = build_prompt_string(get_username(), hostname, cwd);
	free(cwd);
	return (prompt);
}
