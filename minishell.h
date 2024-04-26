/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#             */
/*   Updated: 2024/01/27 11:09:50 by evdos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>

# define FALSE			0
# define TRUE			1

# define NO				0
# define YES			1
# define NEITHER		2

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1
# define ERROR_FOUND	1
# define EXIT_NO_CMD	2

# define B_FORKABLE		0
# define B_UNFORKABLE	1
# define NOT_BUILTIN	2

# define E_SYNTAX	"Error near unexpected token"
# define E_CMD		"Command not found"
# define E_FILE		"File or directory does not exit"
# define E_DIR		"Is a directory"
# define E_MALLOC	"Werror with malloc"
# define E_PIPE		"Error with pipe"
# define E_DUP2		"Error with dup2"
# define E_FORK		"Erro with fork"
# define E_HEREDOC	"Problem: here-document at line 1 delimited by end-of-file"
# define E_HOME		"HOME not set"
# define E_ARGS		"Too many arguments"
# define E_NUM		"You must add a numeric argument"
# define E_EXPORT	"Identifier not Valid"

extern int	g_exit_status;

typedef enum e_type
{
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR2_IN,
	T_REDIR2_OUT,
	T_OTHER,
	T_COMMAND,
	T_FILE_IN,
	T_FILE_TR,
	T_HEREDOC,
	T_FILE_AP,
	T_EMPTY,
}	t_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**f_redin;
	char			**f_redout;
	int				*t_redin;
	int				*t_redout;
	int				has_heredoc;
	int				fd_in;
	int				fd_out;
	int				index;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	char			*input;
	char			**envp;
	char			**paths;
	int				**pipe_fd;
	int				n_pipes;
	pid_t			pid_heredoc;
	pid_t			*pid;
	int				core_dump;
	int				file_error;
	int				heredoc_signal;
	int				heredoc_status;
	t_env			*env_lst;
	t_token			*token_lst;
	t_cmd			*cmd_lst;
}	t_minishell;

// main.c
void	ft_iniciar(t_minishell *ms);
void	ft_handler_especial(char *input);
void	ft_libertar_memoria(t_minishell *ms, int free_pipes, int exit_flag);

// PARSING _____________________________________________________________________

// parser.c
int		ft_parsering(t_minishell *ms, char *input);
int		ft_verificar_aspas(char *input);
void	ft_remover_aspas(t_minishell *ms);
char	*ft_remove_quotes(char *cmd, int new_len, int i);

// tokenizer.c
void	ft_tokenizer(t_minishell *ms, char *input);
int		ft_add_token(t_token **token_lst, char *input, t_type type);
int		ft_add_command_token(t_token **token_lst, char *input, t_type type);

// tokenizer_utils.c
t_token	*ft_new_token(char *input, t_type type);
void	ft_add_token_back(t_token **token, t_token *new_token);

// syntax_checker.c
int		ft_verificar_sintax(t_minishell *ms, t_token *token);

// expander.c
void	ft_expander(t_minishell *ms, t_token *token);
void	ft_expand_command(t_minishell *ms, t_token *token);
char	*ft_get_key(char *cmd);
char	*ft_get_env_value(t_env **env_lst, char *key);
char	*ft_replace_content(char *cmd, char *key, char *value);

// command_table.c
int		ft_command_table_creator(t_minishell *ms);
int		ft_command_table_helper(t_minishell *ms);
int		ft_command_table_exception(t_minishell *ms, t_token *first, int n_args);

// command_table_utils.c
t_cmd	*ft_new_cmd(t_token *first, int n_args);
char	**ft_get_args(t_token *first, int n_args);
char	**ft_add_files(t_token *first, t_type type1, t_type type2);
int		*ft_add_types(t_token *first, t_type type1, t_type type2);
void	ft_add_cmd_back(t_cmd **cmd_table, t_cmd *new_cmd);

// ENVIRONMENT _________________________________________________________________

// environment_lst.c
void	ft_init_env(t_env **env, char **envp);
t_env	*ft_new_env(char *key, char *value);
void	ft_add_env_back(t_env **env_lst, t_env *new_env);
char	**ft_path(t_env *env_lst);

// EXECUTION ___________________________________________________________________

// executer.c
void	ft_exec(t_minishell *ms);
void	ft_exec_one_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
int		ft_execute_mult_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_external(t_minishell *ms, t_cmd *curr, char *cmd);

// redir_handler.c
int		ft_cmd_has_redir(t_cmd *cmd);
void	ft_handle_redir(t_minishell *ms, t_cmd *curr);
int		ft_open_fd(t_minishell *m, t_cmd *c, char *filename, t_type filetype);
void	ft_close_fds(t_cmd *curr);
int		ft_perror_fd(t_cmd *c, char *filename, t_type filetype);

// heredoc_handler.c
int		ft_handle_heredoc(t_minishell *ms, char *delimiter);
void	ft_create_heredoc(t_minishell *ms, char *delimiter);
char	*ft_expand_heredoc(t_minishell *ms, char *line);

// pipes_handler.c
int		ft_count_pipes(t_cmd *cmd_lst);
void	ft_open_pipes(t_minishell *ms);
void	ft_handle_pipes(t_minishell *ms, t_cmd *curr);
void	ft_close_pipes(t_minishell *ms);

// BUILTINS ____________________________________________________________________

// cd.c
void	ft_cd(t_minishell *ms, t_cmd *curr);
int		ft_cd_helper(t_minishell *ms, t_cmd *curr, int arg_flag);

// echo.c
void	ft_echo(t_minishell *ms, t_cmd *curr);
int		ft_get_start_index(char **args);
int		ft_tilde_expander(t_minishell *ms, t_cmd *curr, int i);
void	ft_print_argument(char *s);

// env.c
void	ft_env(t_minishell *ms, t_cmd *cur);

// exit.c
void	ft_exit(t_minishell *ms, t_cmd *curr);
int		ft_is_num(char *s);

// export.c
void	ft_export(t_minishell *ms, t_cmd *curr);
int		ft_export_variable(t_minishell *ms, t_cmd *curr, int i);
void	ft_export_list(t_minishell *ms, t_cmd *curr);
void	ft_sort_env(t_env *env);
void	ft_swap_env(t_env *curr, t_env *next);

// pwd.c
void	ft_pwd(t_minishell *ms, t_cmd *curr);

// unset.c
void	ft_unset(t_minishell *ms, t_cmd *curr);
void	ft_export_unset(t_minishell *ms, char *arg);
void	ft_unset_unset(t_minishell *m, t_cmd *c, t_env *e, t_env *p);

// UTILS _______________________________________________________________________

// main_utils.c
int		ft_perror(t_minishell *ms, char *error, int free_flag, char *file);
int		ft_espacos(char *str);
int		ft_contar_redir(t_token *first, t_type type1, t_type type2);
void	ft_has_heredoc(t_minishell *ms);

// parsing_utils.c
int		ft_verificar_espacos(char c);
int		ft_simbolo(char c);
int		ft_contar_aspas(char *s);
int		ft_aspas_simples(char *cmd, char *stop);
int		ft_aspas_duplas(char *cmd, char *stop);

// execution_utils.c
int		ft_is_forkable(t_minishell *ms, int execution_flag);
void	ft_index_cmd(t_minishell *ms);
void	ft_waitpid_handler(t_minishell *ms, int i, pid_t pid, int exec_flag);
char	*ft_encontar_path(char *cmd, char *possible_paths);
void	ft_cmd_com_multiplo_helper(t_minishell *ms, t_cmd *curr, int flag);

// free_utils.c
void	ft_libertar_lista_token(t_token **token_lst);
void	ft_libertar_lista_cmd(t_cmd **cmd_table);
void	ft_libertar_env_lista(t_env **env_lst);
void	ft_libertar_str_array(char **str_array);
void	ft_libertar_pipes(t_minishell *ms);

// builtins_utils.c
bool	ft_validar_cmd_option(char **args);
void	ft_builtin_error(t_minishell *ms, t_cmd *curr, char *err, int ex_code);
char	*ft_find_env(t_env *env_lst, char *find);
void	ft_update_env(t_env **env_lst, char *key, char *update);

// builtins_utils_2.c
bool	ft_verificar_args(char *arg, int export_flag);
void	ft_caminho_n_valido(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_build_envp(t_minishell *ms);

// SIGNALS _____________________________________________________________________

// signals.c
void	ft_signals(void);
void	ft_signals_heredoc(void);
void	ft_signals_child(t_minishell *ms);

// handlers.c
void	ft_libertar_heredoc(int signum, t_minishell *ms);
void	ft_handler_sigint(int signum);
void	ft_handler_heredoc(int signum);
void	ft_handler_child(int signum);

#endif
