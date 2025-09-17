# Program file name
NAME	= minishell

# Compiler and compilation flags
CC		= cc
CFLAGS	= -Werror -Wextra -Wall

# Build files and directories
SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
SRC		= 	main.c \
			utils_dg/init_data.c \
			env_dg/env.c \
			env_dg/env_set.c \
			lexer_d/parse_user_input.c \
			lexer_d/tokenization.c \
			lexer_d/tokenization_utils.c \
			lexer_d/check_if_var.c \
			lexer_d/lexer_grammar.c \
			lexer_d/token_lst_utils.c \
			lexer_d/token_lst_utils_2.c \
			expansion_d/var_expander.c \
			expansion_d/var_expander_utils.c \
			expansion_d/identify_var.c \
			expansion_d/quotes_handler.c \
			expansion_d/quotes_remover.c \
			expansion_d/recover_value.c \
			expansion_d/replace_var.c \
			parser_d/create_commands.c \
			parser_d/parse_word.c \
			parser_d/fill_args_echo.c \
			parser_d/fill_args_echo_utils.c \
			parser_d/fill_args_default.c \
			parser_d/parse_input.c \
			parser_d/parse_trunc.c \
			parser_d/parse_append.c \
			parser_d/parse_heredoc.c \
			parser_d/parse_heredoc_utils.c \
			parser_d/parse_pipe.c \
			parser_d/cmd_lst_utils.c \
			parser_d/cmd_lst_utils_cleanup.c \
			builtins_d/export_builtin.c \
			builtins_d/unset_builtin.c \
			builtins_d/cd_builtin.c \
			builtins_d/env_builtin.c \
			builtins_d/pwd_builtin.c \
			builtins_d/echo_builtin.c \
			builtins_d/exit_builtin.c \
			execution_g/execute.c \
			execution_g/execute_cmd.c \
			execution_g/execute_utils.c \
			execution_g/parse_path.c \
			redirections_g/pipe.c \
			redirections_g/file_io.c \
			utils_dg/exit.c \
			utils_dg/error.c \
			utils_dg/cleanup.c \
			signals_g/signal.c \

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I $(INC_PATH) -I $(LIBFT_PATH)

# Libft files and directories
LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

# Colores para mensajes bonitos
GREEN = \033[1;32m
RED = \033[1;31m
RESET = \033[0m

# Main rule
all: $(OBJ_PATH) $(LIBFT) $(NAME)

# Objects directory rule
$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/builtins_d
	@mkdir -p $(OBJ_PATH)/lexer_d
	@mkdir -p $(OBJ_PATH)/expansion_d
	@mkdir -p $(OBJ_PATH)/parser_d
	@mkdir -p $(OBJ_PATH)/env_dg
	@mkdir -p $(OBJ_PATH)/execution_g
	@mkdir -p $(OBJ_PATH)/utils_dg
	@mkdir -p $(OBJ_PATH)/redirections_g
	@mkdir -p $(OBJ_PATH)/signals_g
	@mkdir -p $(OBJ_PATH)/debug

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -lreadline -o $(NAME)
	@echo "[100%] $(GREEN)Compilation successful!$(RESET)"

# Libft rule
$(LIBFT):
	@make -s -C $(LIBFT_PATH)

# Clean up build files rule
clean:
	@$(MAKE) -s clean -C $(LIBFT_PATH)
	@$(RM) -rf $(OBJ_PATH)
	@echo "[100%] $(RED)Cleaning object files...$(RESET)"

# Remove program executable
fclean: clean
	@$(MAKE) -s fclean -C $(LIBFT_PATH)
	@$(RM) -f $(NAME)
	@echo "[100%] $(RED)Cleaning everything...$(RESET)"

# Clean + remove executable
re: fclean all

.PHONY: all re clean fclean