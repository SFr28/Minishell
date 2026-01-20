/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:10:56 by sovincen          #+#    #+#             */
/*   Updated: 2025/03/06 18:17:55 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# define _XOPEN_SOURCE 700
# define _GNU_SOURCE

typedef struct s_env
{
	char			*name;
	char			*var;
	int				env_type;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			*path;
	char			**args;
	char			*infile;
	char			*outfile;
	int				fd_in;
	int				fd_out;
	int				builtin;
	pid_t			pid;
	int				status;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_token
{
	int				token;
	char			**argv;
	char			*infile;
	char			*outfile;
	int				argc;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	int		saved_stdin;
	int		saved_stdout;
	int		nb_cmd;
	t_cmd	**cmds_list;
}			t_data;

//Environments
void	init_env(int argc, char **argv, char **env, t_env **env_ms);
char	**split_env(char *var);
void	free_split(char **s);
char	**env_lsttoarr(t_env **env_lst);
char	**env_lsttoarr(t_env **env_lst);
t_env	*new_envvar(char *name, char *var, int env_type);
void	env_addback(t_env **env_ms, t_env *new_var);
int		env_size(t_env **env);
int		env_size(t_env **env);
void	delone_env(t_env *to_delete);
void	clear_env(t_env **env_ms);
void	adjust_shlvl(t_env **env_ms);

//Builtins
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_cd(char **args, t_env **env_ms);
int		ft_env(char **args, t_env **env_ms);
int		ft_unset(char **args, t_env **env_ms);
int		ft_export(char **args, t_env **env_ms);
int		ft_exit(char **args, t_env **env_ms, t_data *data);
int		ft_miaou(void);

//split_cmd
char	**ft_split_cmd(char *str);
char	*join_cmd(char *table, char *str, int i);
char	**ft_subsplit(char **table, t_env **env);
char	*ft_strdup_cmd(char *str, char *table);
char	*ft_strcpy_quote(char *table, char *cmd);
char	**ft_freetab_cmd(char **table);
char	*ft_change_var(char *table, char *cmd, t_env **env, int i);
int		check_dollar(char *table);
int		ft_condition(char *table, char **cmd, int j);
int		ft_quote(char *str, int i);
int		count_quotes(char *str);
int		ft_count_cmd(char *str, int i, int count, int q);
int		ft_len_cmd(char *str, char c);
int		ft_subcount(char **table);
int		check_cmds(char **cmd);
int		ft_is_space(char c);

//parsing
int		treat_line(char *line, t_env **env_ms);
t_token	**ft_parsing(char **cmd, t_token **tokens);
int		ft_sub_par(char **cmd, t_token *temp, int i);
int		ft_create_tokens(char *cmd, t_token **token);
int		ft_complete_token(char **cmd, t_token *element, int count, int i);
void	ft_file(char *cmd, t_token *element);
t_token	*ft_new_token(char *cmd);
void	ft_token_add_back(t_token **token, t_token *new);
t_token	*ft_last_token(t_token *token);
void	ft_set_token(char *cmd, t_token *element);
void	ft_free_tokens(t_token **tokens);

//Redirection
int		open_file(char *file, int redir_type);

//Build_cmds
t_cmd	**build_cmds(t_token **tokens, t_env **env);
int		ft_create_cmds(t_cmd **cmd, t_cmd *element, t_token *temp);
t_cmd	*ft_new_cmd(t_token *temp);
void	ft_complete_cmd(t_cmd *element, t_token *temp);
void	ft_cmd_add_back(t_cmd **cmd, t_cmd *new);
int		ft_find_cmds(t_cmd **cmd, t_env **env);
void	ft_find_path(t_cmd *cmd, t_env *env);
void	ft_free_cmds(t_cmd **cmds);
char	*ft_pre_memcpy(char *src, char *dest);
char	*ft_join_path(char *s1, char *s2);

//Execution
void	execution(t_cmd **cmds_list, t_env **env_ms);
int		execute_cmd(t_cmd *cmd, t_env **env_ms, t_data *data);
int		error_exit(char *msg_err);
int		error_execute(t_cmd *cmd, t_env **env_ms, char **env_arr, int status);
void	clean_cmds(t_cmd **cmd_list);
int		execute_builtins(t_cmd *cmd, t_env **env_ms, t_data *data);
int		execute_single_cmd(t_data *data, t_env **env_ms);
void	set_input(t_cmd *cmd);
void	restore_std(int saved_stdin, int saved_stdout);

//Utils
int		cmdlist_size(t_cmd **cmds_list);
int		ft_count_args(char **args);
int		check_for_rm(t_cmd *cmd);

//Signals
void	ft_ctrl_c(int signum);
void	sig_child(int signum);
void	sig_heredoc(int signum);

#endif
