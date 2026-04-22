# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/27 15:31:10 by gpirozzi          #+#    #+#              #
#    Updated: 2025/05/14 15:08:46 by gpirozzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell
SRC =	./main/main.c ./main/main_utils.c ./main/cmd_execution.c\
		./tokens/tokenize_input.c ./tokens/for_merge_export.c\
		./tokens/assign_token_type.c ./tokens/check_sintax.c\
		./tokens/check_sintax_utils.c\
		./tokens/for_merge_echo.c ./tokens/handle_tokens.c\
		./command_list/create_command_list.c ./command_list/utils_cmd_list.c\
		./pipes/create_pipe_list.c ./pipes/pipes.c\
		./builtin/pwd.c ./builtin/ft_echo.c ./builtin/ft_cd.c ./builtin/exit.c\
		./builtin/env.c ./builtin/export.c ./builtin/unset.c\
		./redirections/handle_redirections.c ./redirections/handle_heredoc.c\
		./common_utils/utils_token.c ./common_utils/utils_token_pt2.c\
		./common_utils/free_functions.c ./common_utils/utils_env.c\
		./common_utils/quotes_finder.c ./common_utils/utils_fd.c\
		./common_utils/signal_flag.c  ./common_utils/utils_pipes.c\
		./common_utils/utils_env_pt2.c ./common_utils/redir_utils.c\
		./common_utils/write_errors.c\
		./common_utils/utils_export_unset.c\
		./system_commands/system_commands.c\

LDFLAGS = -lreadline -lhistory

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/

all: $(NAME)


$(LIBFT):
		@$(MAKE) -C $(LIBFT_DIR) --silent

$(NAME): $(SRC) $(LIBFT)
		@$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME) $(LDFLAGS)
		@echo "Creating the executable..."

clean:
		@$(MAKE) clean -C $(LIBFT_DIR) --silent
		@echo "Cleaning object files..."

fclean: clean
		@rm -rf $(NAME)
		@$(MAKE) fclean -C $(LIBFT_DIR) --silent
		@echo "Full clean done..."

re: fclean all

vall: all clean
		valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re
