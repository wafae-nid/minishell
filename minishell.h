/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:40:40 by agaladi           #+#    #+#             */
/*   Updated: 2025/05/20 19:51:15 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include "printf/ft_printf.h"

# define YELLOW "\033[93m"
# define RESET "\033[0m"
# define BOLD "\033[1m"
# define ORANGE "\033[38;5;214m"
# define GREEN_FG "\033[92m"
# define RED "\033[31m"
# define F_COLOR "\033[96m"
# define PINK "\033[38;5;13m"

# define CD_ERROR  "cd: error retrieving current directory: getcwd: cannot access \
parent directories: No such file or directory\n"

# define PERM 126
# define ERROR 1
# define NOENT 127

typedef struct e_msgs
{
	char	*prompt_msg1;
	char	*prompt_msg2;
	char	*valid_arrow;
	char	*unvalid_arrow;
}	t_msgs;

typedef enum e_tokenType
{
	RED_IN,
	RED_OUT,
	APPEND,
	HERE_DOC_EXP,
	HERE_DOC,
	EXPAND,
	COMMAND,
	PIPE
}	t_tokenType;

typedef struct s_token
{
	t_tokenType		type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_opp
{
	t_tokenType		operator;
	char			*arg;
	struct s_opp	*next;
}	t_opp;

typedef struct s_com
{
	char			**command;
	t_opp			*operator;
	struct s_com	*next;
}	t_com;


typedef struct s_pipe
{
	int		*curr_pipe;
	int		*prev_pipe;
	int		num_commands;
	int		curr_command;
	pid_t	*pids;
}	t_pipe;
// execution types - start
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_com			*command;
	t_env			*env;
	t_env			*export;
	char			*pwd;
	char			**heredoc_files;
	int				exit_status;
	int				heredoc_count;
	int				heredoc_index;
	char			*last_exec_cmd;
	struct termios	term;
}	t_shell;
// execution types - end

typedef struct s_expand_data
{
	char	**token_val;
	t_env	*env;
	int		exit_status;
	int		j; // Output index
	bool	in_double_q; // Double quote state
	bool	in_single_q; // Single quote state
}	t_expand_data;

//garbage collector

typedef enum s_type
{
	LOCAL,
	GLOBAL
}			t_type;

typedef struct s_node
{
	void			*ptr;
	struct s_node	*next;
}	t_node;

typedef struct s_memory_list
{
	t_node	*head;
	t_node	*tail;
}	t_memory_list;


void		add_memory(void *ptr, t_type type);
void		*gc_malloc(size_t size, t_type type);
void		gc_free_all(t_type type);
// execution prototypes
int			set_exit_status(int *status);
int			ft_echo(char **args);
int			ft_env(t_env *env);
char		*ft_get_var_value(t_env *env, const char *key);
int			init_shell_data_config(t_shell *data, char **envp);
void		ft_printf_envs(t_env *env);
int			ft_cd(char **args, t_shell *data);
int			ft_unset(char **args, t_shell *data);
t_env		*create_env_node(char *env_str);
t_env		*convert_env_to_list(char **envp);
t_env		*init_env(char **envp);
int			ft_pwd(t_shell *data);
int			ft_exit(char **args, int exit_status);
int			ft_environ(char **args, t_shell *data);
int			ft_environ_command(t_env **my_env,
				const char *key, const char *value);
int			ft_execute_builtin(t_shell *data);
int			ft_execute_command(t_shell *data);
int			ft_execute_external(char **args, t_shell *data, t_com *command);
char		*find_command(char *cmd, char **p_env);
char		**env_to_array(t_env *env);
int			is_builtin(const char *cmd);
void		ft_get_vars(t_env *exp);
int			ft_set_vars(t_env **my_export_env,
				const char *key, const char *value);
char		*extract_key(char *str);
char		*extract_value(char *str);
int			is_var_exist(char *var, t_env *expo);
int			ft_check_key(const char *arg, const char *value);
char		*ft_get_var_value(t_env *env, const char *key);
char		*get_operation(char *arg);
void		ft_set_mini_env_config(t_env **path, t_env **pwd,
				t_env **shlvl, t_env **last_command);
t_env		*create_mini_env(void);

// pipes prototypes
void		cleanup_pipes(t_pipe *pipex);
void		killall(t_pipe *pipex);
int			count_pipes(t_com *command);
char		***split_commands(t_com *commands, int num_commands);
void		free_commands(char ***commands, int num_commands);
int			ft_execute_pipeline(char ***commands,
				int num_commands, t_shell *data);
void		update_prev_pipe(int *prev_pipe, int *curr_pipe, int is_not_last);
void		ft_init_pipe(t_pipe **pipe, int num_commands);
// redirections
int			handle_redirections(t_shell *data);
int			setup_input_redirection(const char *infile,
				int is_here_doc, t_shell *data);
int			setup_output_redirection(const char *outfile, int is_appended);
void		restore_std_in_out(int stdout_copy, int stdin_copy);
void		redirect_to_pipe_fds(t_shell *data, t_pipe *pipe);
int			is_redirection_in(t_tokenType operator);
int			is_redirection_out(t_tokenType operator, char *file);
int			valid_operator(t_tokenType operator_type,
				int *flags, int *default_fd);
void		close_all_fds(int *fds, int count);
void		handle_files_redirections(t_opp *curr_op, t_shell *data);
int			heredoc_count(t_com *command);
char		**fill_heredoc_files(int count);
void		ftputstr_fd(int fd, char *s);
int			handle_redirection_loop(t_shell *data, t_opp *cur_op);
void		open_heredoc_helper(char **files, int *fd, int *count);
void		open_heredoc(char **files, t_opp *op, int *count, t_shell *data);
void		heredoc_cleanup(int *fd, char *str);
void		handle_heredoc(t_shell *data);
int			ft_read_from_heredoc(t_shell *data);
void		handle_sig(int sig);
void		rm_heredoc_files(t_shell *data);
void		heredoc_count_check(int count);
void		open_tty(void);
void		close_pipe_fds(t_pipe *pipe);
void		close_afrer_fork(t_pipe *pipex);
int			heredoc_one_pipe(t_com *command);
// LIBFT Prototypes
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *str);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2, t_type type);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_isalnum(int c);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strncpy(char *dest, const char *src, int n);
int			first_occurence(char *str, char c);
char		**env_to_array(t_env *env);
// utils
int			cstm_strcmp(char *str1, char *str2);
void		add_lstback(t_opp *operators, t_opp *to_add);
t_token		*last_token(t_token *token);
char		**cstm_split(const char *str, const char *delims);
char		*ft_itoa(int n);
int			is_op(char c);
int			ft_isnum(char c);
void		remove_abg_command(t_com **com);
// tokenizer
int			is_quote(char *str);
int			is_rederection(char *str);
char		*add_spaces(char *str);
void		switch_char(char **str, char to_find, char character);
char		*format(char *str);
char		*format_and_switch(char *input);
t_token		*tokenizer(char *input, t_env *env, int *exit_status);
void		heredoc_type_set(t_token **token);
bool		has_quotes(char *str);
// expand
void		expand_tokens(t_token *token, t_env *env, int *exit_status);
void		expand(char **token_val, t_env *env,
				int *exit_status, bool is_herdoc);
void		handle_expansion_loop(t_expand_data *exp_data,
				char *output, bool is_herdoc);
int			is_valid_for_expansion(char c);
void		handle_variable_expansion(t_expand_data *exp_data,
				char *output, int *i);
void		handle_regular_characters(t_expand_data *exp_data,
				char *output, int *i);
void		copy_non_space(t_expand_data *exp_data, char *output, int *i);
int			ft_isspace(char c);
char		*get_expand_val(char *str, t_env *env, int *i, int exit_status);
void		handle_quotes_state(char c, bool *in_single_q, bool *in_double_q);
int			calculate_size(char *str, t_env *env, int exit_status);
t_com		*set_command(t_shell *data_config, char *cmd_line_args);
int			is_spaces(char *str);
void		disable_echoctl(struct termios *term);
void		signals_init(void);
void		setup_signal_handlers(void);
// lexer
void		trim_quotes(t_token **token);
int			check_pipes(t_token *token);
int			is_red(t_tokenType type);
t_tokenType	red_type(t_token *token);
t_opp		*new_op(t_token **token);
t_com		*new_com(t_token *token);
bool		check_quote_syntax(char *input);
t_com		*create_cmds(t_token *token);
void		print_command(t_com *command);
void		print_opp(t_opp *opera);

void		print_token(t_token *token);
// errors
void		*error_handler(t_token *head, int *exit_status);
void		error(void);
int			syntax_error(t_token *token);
void		execute_command(t_shell *data, char **commands);
const char	*get_path(const char *cmd, t_env *env);
// prompt
char		*prompt(t_shell *data);
int			ft_isalpha(char c);

/* ************************************************** UR CODE ************************************************************ */

// typedef struct s_environ
// {
// 	char *var;
// 	char *value;
// 	struct s_environ *next;
	
// } t_environ;

typedef struct s_environ
{
	char *var;
	char *operator;
	char *value;
	struct s_environ *next;
} t_environ;

void execution_entery(t_com *command, char *PWD, char *oldprompt);
void  pwd_execution(t_com *command);
void echo_execution(t_com *command);
t_environ *making_the_environ_struct(void);
// int count_lengh_value_str(char *str);
// int count_lengh_var_str(char *str);
//char  **split_environ(char *str);
t_environ  *ft_lstnew_environ( char *environ);
void	ft_lstadd_back_environ(t_environ **lst, t_environ *new);

void executing_env(t_environ **environ);
void cd_execution(t_com *command, char *PWD);
char	*ft_strjoin_(const char *s1, const char *s2);
int export_parssing(t_com *command, char *oldprompt, t_environ **environ);
void unset_executing(t_com *command, t_environ **environ);

#endif
