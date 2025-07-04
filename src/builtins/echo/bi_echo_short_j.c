
#include "minishell.h"

/*depending on a variable exported that has -nnnn as an echo it will pass...*/
/*...them or not. So I will send that start point to write the parsed file*/
size_t	check_argument(t_input *in, int parsed_n)
{
	size_t	i;
	size_t	n_repeated;

	i = 1;
	n_repeated = 1;
	if (parsed_n)
		in->echo_error_n_arg = 0;
	if (!in->parsed || !in->parsed[0])
		return (0);
	while (in->parsed[i] && in->parsed[i] != ' ')
	{
		if (in->parsed[i++] != 'n' || in->parsed[0] != '-')
		{
			n_repeated = 0;
			if (parsed_n)
				in->echo_error_n_arg = 1;
		}
	}
	if (ft_strncmp(in->parsed, "-n", 2) != 0 && parsed_n)
		in->echo_error_n_arg = 1;
	if (in->echo_error_n_arg == 0 && n_repeated)
		i = check_more_n(in);
	else
		i = 0;
	return (i);
}

size_t	check_redirects(t_input *in, size_t i)
{
	size_t	j;

	if (is_valid_arg(&in->parsed[i]))
	{
		in->echo_error_n_arg = 0;
		while (in->parsed[i] && (in->parsed[i] != ' '))
			i++;
		if (in->parsed[i] == ' ')
			i++;
		j = i;
		while (in->parsed[i] && in->parsed[j] == '-')
		{
			(i)++;
			while (in->parsed[i] && in->parsed[i] == 'n')
				(i)++;
			if (in->parsed[i] != ' ')
				break ;
			else if (in->parsed[i] == ' ')
				j = ++(i);
		}
		if (in->parsed[i])
			i = j;
	}
	return (i);
}

/*if >file echo will not get inside "echo" 5, as it will the last one...*/
/*...so in that case it dont have to print anything. other case will print it*/
/*wont do it if ''>file or ">"file*/
void	print_final_echo(t_input *in, int fd, size_t start)
{
	// Caso especial: echo con redirección de input, imprimir desde el input original
	if (in->split_exp && in->split_exp[0]
		&& (in->split_exp[0][0] == '<' || in->split_exp[0][0] == '>')
		&& (in->status_exp[0] == 0))
	{
		// Buscar el inicio del argumento real en el input original
		const char *cmd = "echo";
		size_t cmd_len = 4;
		size_t offset = 0;
		// Saltar espacios iniciales
		while (in->input[offset] && (in->input[offset] == ' ' || in->input[offset] == '\t'))
			offset++;
		// Saltar la palabra 'echo'
		if (ft_strncmp(in->input + offset, cmd, cmd_len) == 0)
			offset += cmd_len;
		// Saltar los espacios después de 'echo'
		while (in->input[offset] && (in->input[offset] == ' ' || in->input[offset] == '\t'))
			offset++;
		// Imprimir desde ahí hasta el final, respetando todos los espacios y comillas
		write(fd, in->input + offset, ft_strlen(in->input + offset));
	}
	else
	{
		write(fd, in->parsed + start, ft_strlen(in->parsed + start));
	}
	if (in->echo_error_n_arg == 1 || in->total_pipes > 0)
		write(fd, "\n", 1);
}

/*I want to check if the echo comes from $VAR or not. so that is the reason...*/
/*...of running the input to find first char appart from ' or ". If so, the...*/
/* -n that rules is the one in in->parsed*/
/*after second start, the if will look for cases as >file echo only to not...*/
/*...print anything and only print if something is behind that echo*/
void	echo_short(t_input *in, int fd)
{
	int		parsed_n;
	size_t	start;
	size_t	i;

	i = 0;
	parsed_n = 0;
	while (in->input && (in->input[i] == '"' || in->input[i] == '\''))
		i++;
	if (in->input[i] == '$')
		parsed_n = 1;
	else if (in->args && in->args[0] == '$' && in->split_exp && in->split_exp[0]
		&& in->split_exp[1] && is_valid_arg(in->split_exp[1]))
		parsed_n = 1;
	if (parsed_n)
		in->echo_error_n_arg = 1;
	if (in->total_redirections > 0)
		start = check_redirects(in, 0);
	else
		start = check_argument(in, parsed_n);
	print_final_echo(in, fd, start);
	in->last_exit_code = 0;
}
