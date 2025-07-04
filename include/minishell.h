
#ifndef MINISHELL_H
# define MINISHELL_H

/*
** ========================== External Headers ===========================
*/

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

/*
** ========================== Internal Headers ===========================
*/

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

/*
** ============================= Defines =================================
*/

// Status defines
# define EPTY_NSP 0
# define EPTY_SP 1
# define SQUO_NSP 10
# define SQUO_SP 11
# define DQUO_NSP 20
# define DQUO_SP 21

// Character sets
# define D_Y_ODDCHAR "~%^=+}]:;/.,·"
# define N_ODDCHAR "!@*-#`(){["
# define BUFFER 100

// Color defines
# define COLOR_RED "\001\033[1;31m\002"
# define COLOR_GREEN "\001\033[1;32m\002"
# define COLOR_YELLOW "\001\033[1;33m\002"
# define COLOR_BLUE "\001\033[1;34m\002"
# define COLOR_MAGENTA "\001\033[1;35m\002"
# define COLOR_CYAN "\001\033[1;36m\002"
# define COLOR_RESET "\001\033[0m\002"
# define COLOR_GRAY "\001\033[1;90m\002"
# define COLOR_LIGHT_CYAN "\001\033[1;96m\002"

// Prompt
# define PROMPT COLOR_LIGHT_CYAN"%s@%s:%s"COLOR_RESET"$ "

/*
** ========================== Data Structures ============================
*/

typedef struct s_split
{
	char	*s;
	char	c;
	size_t	words;
	size_t	start;
	int		error;
	int		quotes;
	char	*split_aux;
}			t_split;

typedef struct s_input
{
	// Input/Output
	char	*input;
	char	*parsed;
	char	*filename;
	int		inputfd;
	int		outputfd;

	// Command and arguments
	char	**input_split;
	char	**split_exp;
	char	*token;
	char	*command;
	char	*args;

	// Environment
	char	**envp;
	char	**local_envp;
	size_t	env_len;
	int		env_n;

	// Status and control
	int		*status;
	int		status_exp[100];
	int		from_expand;
	int		spaced;
	int		status_checked;
	pid_t	last_exit_code;
	bool	is_script;

	// Word and token tracking
	size_t	realloc_counter;
	size_t	word_after_command;
	size_t	word_after_arg;
	size_t	input_words;
	size_t	word;
	size_t	dollars;
	size_t	idollar;

	// Command execution
	int		total_pipes;
	int		total_redirections;
	int		cmd;
	int		cmd_start;
	int		cmd_end;
	int		num_cmds;

	// Misc
	int		echo_error_n_arg;
	char	*last_dollar_;
}			t_input;

/*
** ====================== Global Variables ==============================
*/

extern volatile sig_atomic_t	g_signal_received;

/*
** ====================== Function Prototypes ===========================
*/

/*
** =========================== Main Functions ===========================
*/

// Initialization and Cleanup
void	clean_all(t_input *input, int error);
void	init_input_struct(t_input *input);
void	ft_input_free(t_input *input);

// History and Input
void	ft_manage_history(char *input, bool clean);

// Signal Handling
void	init_sigaction(struct sigaction *sa);
void	ctrlc_handler(int sig);
void	disable_echoctl(void);
void	one_hundred_thirty(t_input *input);
void	one_hundred_thirtyone(t_input *input);

/*
** ========================== Parsing Functions =========================
*/

// Main Parsing
void	parsing(t_input *in);
void	ft_manage_input(t_input *input);
void	update_input(t_input *input, int i, bool lonely);
void	ft_compose_parsed(t_input *input);
void	quit_parsing(t_input *in, int stdout_save);

// Command and Argument Processing
void	compose_command_args(t_input *in);
void	compose_arg(t_input *in, size_t word);
void	compose_command(t_input *in);
void	compose_token(t_input *in);
void	dynamic_input(t_input *in, size_t k);
void	dynamic_command(t_input *in, size_t k);
void	dynamic_arg(t_input *in, size_t k);
void	remove_control_char(char *string);

// Expansion
void	expand_dollar(t_input *in, size_t *i, size_t *j, size_t *k);
void	save_rest_no_env(t_input *in, size_t w, size_t *i, size_t *k);
void	save_rare_cases(t_input *in, size_t w, size_t *i, size_t *k);
void	save_valid_env_variable(t_input *n, size_t w, size_t *i, size_t *k);
void	expand_token_dollar(t_input *in, size_t *i, size_t *j, size_t *k);
void	token_valid_env_variable(t_input *n, size_t w, size_t *i, size_t *k);
void	token_rest_no_env(t_input *in, size_t w, size_t *i, size_t *k);
void	token_rare_cases(t_input *in, size_t w, size_t *i, size_t *k);
void	input_check_prev_dollar(t_input *in, size_t *i, size_t *j, size_t *k);
void	save_rare_cases2(t_input *in, size_t *k, char *str, size_t id);
void	token_rare_cases2(t_input *in, size_t *k, char *str, size_t id);
void	do_even_dollars2(t_input *in, size_t w, size_t *i, size_t *k);
void	env_question2(t_input *in, size_t w, size_t *i, size_t *k);
void	save_env_if_even_dollars2(t_input *in, size_t w, size_t *i, size_t *k);
void	do_even_token_dollars2(t_input *in, size_t w, size_t *i, size_t *k);
void	token_env_question2(t_input *in, size_t w, size_t *i, size_t *k);
void	token_env_if_even_dollars2(t_input *in, size_t w, size_t *i, size_t *k);

/*
** ====================== Quote Handling Functions ======================
*/

char	**ft_split_quotes(char const *s, char c, t_input *input);
int		ft_count_quotes_words(t_split *squotes, t_input *input);
void	assign_token_status(t_input *input, t_split *sq, char letter);
char	*sub_split_quotes(t_split *squotes, t_input *input);
int		is_spaced(t_split *sq, size_t i);
int		is_quoted(t_input *input, int word);
char	*ft_last_str(t_input *input, char **str);

/*
** ====================== Built-in Commands ============================
*/

void	ft_echo(t_input *in, int active);
void	echo_short(t_input *in, int fd);
void	ft_pwd(char *args, t_input *input);
void	ft_env(t_input *in, char **envp);
void	ft_export(t_input *input, char ***envp);
void	ft_unset(t_input *input);
void	ft_cd(t_input *input);
void	ft_exit(t_input *in);

/*
** ====================== Execution Functions ==========================
*/

bool	execute_command(t_input *input);
void	ft_manage_pipes(t_input *input);
char	*get_cmd_path_from_env(t_input *input, char **envp, char *cmd);
char	*join_command(char **split_exp, int start, int end);
int		count_pipes(t_input *input);
void	setup_pipe(int *pipefd, int cmd, int num_cmds);
void	handle_fork_error(void);
char	**get_command_args(char **split_exp, int start, int end);
void	child_p_2(t_input *input, t_input *child, int cmd_start, int cmd_end);
void	child_p(int prev_fd, int *pipefd, t_input *input);
void	parent_p(int *prev_fd, int *pipefd, int is_last, char **args);
void	wait_for_children(pid_t last_pid, t_input *input);

/*
** ====================== Redirection Functions =======================
*/

bool	handle_redirection(t_input *input);
void	handle_heredoc_redirection(t_input *input, char *redir);
bool	ft_manage_input_redirection(t_input *input, int i, bool lonely);
bool	ft_manage_output_redirection(t_input *input, int i, bool lonely);
bool	ft_manage_append_redirection(t_input *input, int i, bool lonely);
bool	ft_manage_heredoc_redirection(t_input *input, int i, bool lonely);
void	print_heredoc(char *line, int pipefd);

// Environment Management
void	manage_dollar(t_input *in, size_t w, int spaced);
int		valid_env(const char *str, t_input *in, size_t w);
size_t	validlen_env(const char *str, char c);
size_t	invalidlen_env(const char *str);
void	print_rare_cases(t_input *in, size_t w, size_t *i);
void	print_rest_no_env(t_input *in, size_t w, size_t *i);
void	print_if_spaced_and_valid_env(t_input *in, size_t w, int spaced);
void	print_valid_env_variable(t_input *n, size_t w, size_t *i);
void	space_after_first_invalid_env(t_input *in, size_t w, size_t i, int on);
void	export_print_sorted(char **env);
void	update_shlvl(char **arg);
void	env_add(char ***envp, char *new_var);
void	update_env(t_input *input, char *key, char *value);
char	*get_env_value(char **envp, const char *name);

// Signals
void	init_sigaction(struct sigaction *sa);
void	ctrlc_handler(int sig);
void	heredoc_sigint_handler(int sig);
void	disable_echoctl(void);
void	heredoc_signals(struct sigaction *sa, struct sigaction *sa_old_int,
			struct sigaction *sa_old_quit);
void	restore_signals(struct sigaction *sa_old_int,
			struct sigaction *sa_old_quit);
void	one_hundred_thirty(t_input *input);
void	one_hundred_thirtyone(t_input *input);

// Utils
char	*get_prompt(t_input *input);
int		is_valid_arg(char *str);
size_t	check_more_n(t_input *in);
char	*get_next_line(int fd);

#endif
