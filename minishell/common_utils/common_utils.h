/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:07:12 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 11:45:51 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_UTILS_H
# define COMMON_UTILS_H

# include "../libft/libft.h"
# include "signal_flag.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum s_type
{
	PIPE,//0
	REDIR_IN,//1
	REDIR_OUT,//2
	REDIR_APPEND,//3
	ENV_VAR,//4
	HEREDOC,//5
	COMMAND,//6
	ARGUMENT,//7
	FILE_,//8
	DELIMITER,//9
	QUOTE,//10
	EXIT_STATUS,//11
	SPACES,//12
	GARBAGE,//13
}	t_type;

typedef struct s_exit
{
	int	exit_status;
}	t_exit;

typedef struct s_env
{
	char	**env_copy;
	bool	path_deleted;
	int		exit_status;
}	t_env;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_pipe	t_pipe;

typedef struct s_command
{
	char				*cmd;
	char				**args;
	char				*input;
	char				*output;
	int					append;//0 = truncate / 1 = append / -1 = niente
	bool				pipe_flag;
	bool				open_error;
	t_token				*tokens;
	struct s_command	*next;
}	t_cmd;

typedef struct s_pipe
{
	pid_t			pid;
	int				pipefd[2];
	t_cmd			*cmd;
	t_token			*tokens;
	bool			one_cmd_flag;
	struct s_pipe	*next;
}	t_pipe;

//fds functions
int		check_value_fd(int append_flag, char *file, t_env *env);
int		ft_check_fd(int fd, t_env *env);
bool	ft_found_heredoc(t_token *tokens);
int		ft_for_fd(t_cmd *cmd, t_env *env, int *saved_stdin);
int		handle_input_redirection(char *input_file, int	*saved_stdin);
void	restore_sdin(int *saved_stdin);
//free function
void	free_token(t_token *token);
void	free_cmd(t_cmd *cmd_list);
void	free_pipe(t_pipe *pipe);
void	free_all(t_cmd *cmd, t_env *env);
void	free_all_pipe(t_pipe *head_pipe, t_env *env);
//quote functions
bool	ft_find_squotes(char *str);
bool	ft_find_dquotes(char *str);
bool	ft_find_env_var(char *str);
//env var function
char	*ft_get_env_value(t_env *env, const char *key);
char	*ft_expand_envvar(char *str, t_env *env);
char	*get_var_name(const char *env_var);
bool	check_only_env_var(t_token *tokens);
//print function
void	print_tokens(t_token *tokens);
void	print_command(t_cmd *command);
//signal
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	get_exit_status(int status, t_env *env);
//pipe
bool	has_pipe(t_token *token);
void	set_pipe_flag(t_cmd *head);
//redir utils
void	ft_for_redir(t_cmd *cmd, t_env *env, int fd, int *saved_stdin);
void	ft_for_env_var(char *line, t_env *env, int fd);
void	ft_end_heredoc(t_token *tokens);
int		ft_check_next_redir(t_token *token);
//export utils
char	**ft_env_sorted(char **env);
bool	is_valid_identifier(char *str);
int		ft_find_export_var(t_env *env, char *args);
void	ft_add_var(t_env *env, char **args, int *i);
int		is_valid_unset_arg(char *arg);
//utils token
t_type	get_token_type(char *value, int q_flag, int is_command);
bool	exit_status_var(char *value);
void	add_token(t_token **head, t_token *new_token);
t_token	*new_token(const char *value, t_type type);
bool	is_redir(t_token *tokens);
bool	is_argument(t_token *tokens);
bool	is_space(t_token *tokens);
bool	is_n_sequence(char *str);
void	ft_assign_spaces(t_token *prev, t_token *tokens, int *between_arg);
void	remove_token_node(t_token **head, t_token *target);
//for errors
void	error_ex(const char *error);
#endif
