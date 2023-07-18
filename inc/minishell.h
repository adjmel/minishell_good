/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:13:58 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/04 14:16:52 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <string.h>
# include <stdarg.h>
# include "errors.h"

# define RESET " \e[00m"
# define GREEN "\e[01;32m"
# define RED "\e[01;31m"
# define GREEN_ARROW "\e[01;32m➜  "
# define RED_ARROW "\e[01;31m➜  "
# define HERE_DOC "/tmp/.heredoc"
# define SPACE ' '
# define TAB '\t'



# ifndef DEBUG
#  define DEBUG 0
# endif

enum e_token
{
	RIGHT_ARROW = '>',
	LEFT_ARROW = '<',
	PIPE = '|',
	DOLLAR_SIGH = '$',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"',
	QUESTION_MARK = '?',
	AMPERSAND = '&',
	OPEN_PARENTHESE = '(',
	CLOSE_PARENTHESE = ')',
	ASTERISK = '*',
};

enum e_redirections
{
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
};

enum e_separator
{
	LAST_CMD,
	AND_TOKEN,
	OR_TOKEN,
	PIPE_TOKEN,
};

typedef struct s_redir
{
	int				type;
	int				fd;
	char			*file;
	struct s_redir	*next;
	struct s_redir	*previous;
}	t_redir;

typedef struct s_proc
{
	char			*cmd;
	char			**args;
	int				separator;
	int				error;
	int				level;
	struct s_redir	*head;
	struct s_proc	*next;
	struct s_proc	*previous;
}	t_proc;

typedef struct s_data t_data;

typedef struct s_builtins
{
	char	*name;
	void	(*func)(char **, t_data *data);
}	t_builtins;

typedef struct s_data
{
	char			**env;
	int				errors;
	int				exit_status;
	int				here_doc;
	t_builtins		builtins[7];
	struct s_proc	*head;
}	t_data;


void	rl_replace_line(const char *str, int i);

/* ------------- libft ------------- */
int		ft_tabsize(char **tab);
int		ft_atoi(const char *str);
char	*ft_strdup(char *str);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
int		ft_strlen(char *str);
void	ft_freearr(char **tab);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcjoin(char *s1, char c, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strstr(char *str, char *to_find);
char	**ft_tabdup(char **tab);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_itoa(int n);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strrchr(char *str, int c);
int		ft_dprintf(int fd, const char *s, ...);
char	*ft_getenv(t_data *data, char *str);

/* ------------- parsing ------------- */
void	parsing(t_data *data, char *input);
int		syntax_error(t_data *data, char **lx);
char	**lexer(char *input);
int		empty(t_data *data, char *input);
void	space_skiper(char *str, int *i);
char	**arr_concate(char **tab, char *str);
char	*str_concate(char *s, char c);
char	**alloc_one(void);
int		not_metachar(char c);
void	buffer_reset(char **buffer);
void	parser(t_data *data, char **lx);
t_proc	*pc_new_node(char **args, int sep, int lvl);
void	pc_addback(t_proc **lst, t_proc *new);
char	**ft_subarr(char **tab, int start, int size);
void	rd_addback(t_redir **head, t_redir *new);
t_redir	*rd_new_node(char *file, int type);
void	clear(t_data *data);
char	*absolute_path(t_data *data, char *cmd);
char	*expand(t_data *data, char *str, int quotes);
void	sig_handler(int sig);
int		parentheses_check(t_data *data, char **lx, int i, int *x, int *y);
void	init_list(t_data *data, char **lx);
void	init_rd(t_data *data);
int		get_separator(char **lx, int i);
char	*del_quote(char *str);
void	wildcard(t_proc *proc);
char	**get_dir_files(char *str);
char	*prompt(t_data *data);
int		not_special(char c);
int		is_arrow(char *str);
void	cd_oldpwd(t_data *data);
int		pattern_match(char *filename, char *pattern, int file_i, int patt_i);

/* ------------- builtins ------------- */
void	init_builtins(t_data *data);
int		check_home(t_data *data);
void	cd_home(t_data *data);
int		check_var(t_data *data, char *str);
void	value_inquotes(t_data  *data, int i);
char	*home_path(void);
void	sort_env(t_data *data);
void	set_pwd(t_data *data);
int		valid_ident(char *str);
void	set_oldpwd(t_data *data);
void	re_cd(char **args, t_data *data);
void	re_echo(char **args, t_data *data);
void	re_env(char **args, t_data *data);
void	re_exit(char **args, t_data *data);
void	re_export(char **args, t_data *data);
void	re_pwd(char **args, t_data *data);
void	re_unset(char **args, t_data *data);

/* ------------- execution ------------- */
void	init_session(t_data *data, int argc, char **argv, char **env);
void	init_redirections(t_redir **redir);
void	supervisor(t_data *data);
int		executor(t_data *data, t_proc *proc, int _pipe[2], int prev_pipe[2]);
void	init_inspector_and_exec(t_data *data, t_proc *_, int __[2], int ___[2], int i);
int		priority_condition(t_proc *proc, int level, int token);
void	apply_priorities(t_data *data, t_proc **proc, int *level);
void	dup_and_close(int fd, int new_fd);
void	dup_or_error(t_redir *current);
int		heredoc_and_errors(t_data *data, t_redir **redir, int *status, pid_t *pid);
void	look_for_cmd_not_found(t_data *data);
int		exit_status(int status);
void	check_if_dots(t_data *data, t_proc **proc);
void	check_if_directory(t_data *data, t_proc **proc);
int		is_builtin(char *cmd);
int		is_path(t_data *data);
int		exec_builtin(t_data *data, char *cmd, char **args);
int		exec_builtin_pipe(t_data *data, t_proc *proc, int _pipe[2], int prev_pipe[2]);
void	exec_piped(t_data *data, t_proc *proc, int _pipe[2], int prev_pipe[2]);
int		exec_empty_cmd(t_proc *proc);
void	exec_cmd(t_data *data, t_proc *proc, int _pipe[2], int prev_pipe[2]);
void	wait_for_child(pid_t pid, int _pipe[2], int prev_pipe[2], int *status);
int		exec_builtin_cmd(t_data *data, t_proc *proc, int _pipe[2], int prev_pipe[2]);
void	exec_heredoc(t_data *data, t_redir *current);
int		handle_heredoc(t_data *data, pid_t pid, int *status);
void	close_heredocs(t_data *data);

/* ------------- debugging ------------- */
void	printf_struct(t_data *data);

#endif