NAME = minishell

CC = cc
INC_DIR = -I./include -I./libft -I./ft_printf
CFLAGS = -Wall -Wextra -Werror $(INC_DIR) #-g3 -fsanitize=address 
LDFLAGS = -lreadline -fsanitize=address
AR = ar rcs
RM = rm -rf

GREEN := \033[1;32m
RED := \033[1;31m
RESET := \033[0m

# Source files - Organized by functionality
SRC = 	src/main.c \
		src/utils/clean_all_m.c \
		src/utils/prompt.c \
		src/utils/get_next_line.c \
		src/utils/get_next_line_utils.c \
		src/utils/init_struct_m.c \
		\
		src/builtins/pwd/bi_pwd_m.c \
		src/builtins/env/bi_env_m.c \
		src/builtins/env/bi_env_dollar_j.c \
		src/builtins/echo/bi_echo_short_j.c \
		src/builtins/echo/bi_echo_short_2_j.c \
		src/builtins/echo/bi_echo_m.c \
		src/builtins/echo/bi_echo_dollar_j.c \
		src/builtins/echo/bi_echo_dollar_2_j.c \
		src/builtins/export/bi_export_m.c \
		src/builtins/export/bi_export_utils_m.c \
		src/builtins/cd/bi_cd_m.c \
		src/builtins/unset/bi_unset_m.c \
		src/builtins/exit/bi_exit_j.c \
		\
		src/parser/parsing_j.c \
		src/parser/parsing2_j.c \
		src/parser/manage_token_parsing_j.c \
		src/parser/manage_token_dollars_j.c \
		src/parser/manage_token_dollars2_j.c \
		src/parser/manage_token_dollars3_j.c \
		src/parser/manage_inputs_m.c \
		src/parser/manage_inputs_utils_j.c \
		src/parser/manage_input_dollars_j.c \
		src/parser/manage_input_dollars2_j.c \
		src/parser/manage_input_dollars3_j.c \
		src/parser/split_exp_utils_j.c \
		src/parser/update_inputs_m.c \
		src/parser/realloc_input_j.c \
		\
		src/executor/execute_command_m.c \
		src/executor/execute_command_path_m.c \
		src/executor/redirections_m.c \
		src/executor/redirections_solve_m.c \
		src/executor/redirections_solve_j.c \
		src/executor/manage_pipes_m.c \
		src/executor/manage_pipes_utils_m.c \
		src/executor/manage_pipes_utils2_m.c \
		src/executor/update_env_m.c \
		\
		src/signals/signal_j.c \
		src/signals/signal2_j.c \
		\
		src/history/history_m.c \
		src/splitQuotes/quote_handling.c \
		src/splitQuotes/quote_utils.c \
		src/splitQuotes/token_processing.c \
		src/splitQuotes/token_separation.c \
		src/splitQuotes/word_counting.c

# Object files
OBJ_DIR = obj
OBJS = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

# Create object directories
OBJ_DIRS = $(sort $(dir $(OBJS)))

# Libft directory
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Ft_printf is now inside libft
FTPRINTF = $(LIBFT_DIR)/libftprintf.a

MAKEFLAGS = --no-print-directory

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# FTPRINTF is now built with LIBFT

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)
	@echo "[100%] $(GREEN)Compilation successful!$(RESET)"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ_DIR)
	@echo "[100%] $(RED)Cleaning object files...$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "[100%] $(RED)Cleaning everything...$(RESET)"

re: fclean all

norm:
	@echo "Checking norminette for all source files..."
	@norminette $(shell find ./src ./include -name "*.c" -o -name "*.h")

.PHONY: all clean fclean re norm

.SILENT:
