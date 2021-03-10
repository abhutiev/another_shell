/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 03:50:41 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/24 18:31:08 by sjeffry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define SHL_NAME 					"almostbash: "
# define STANDART_OUTPUT			0
# define TO_RIGHT_REDIR				2
# define TO_LEFT_REDIR				3
# define TO_RIGHT_DOUBLE_REDIR		4
# define CMD_NOT_FOUND				": command not found"
# define NO_FILE_OR_DIR				": No such file or directory"
# define SNTX_ERR_DOUBLE_SEMICOLON	"syntax error near unexpected token `;;'"
# define SNTX_ERR_ONE_SEMICOLON		"syntax error near unexpected token `;'"
# define TOO_MANY_ARGS				": too many arguments"
# define NUM_ARG_REQUIRED			": numeric argument required"
# define SHITTY_CASE				"shitty and multiline cases not in \
subject, but we've tried to handle it"

int					g_lobal;
int					g_signal_mode;

typedef struct s_cd
{
	char			**splitted_directories;
	char			*tmp;
	size_t			i;
	size_t			k;
	char			**splitted_path;
	char			*path;
	char			*save_pwd;
}					t_cd;

typedef struct s_env
{
	char			*name;
	char			*value;
}					t_env;

typedef struct s_gnl_utils
{
	char	*buffer;
	int		eof;
	int		help;
	size_t	i;

}					t_gnl_utils;

typedef struct s_buffer
{
	char			**buff;
	char			*line_1;
	char			*line_2;
	size_t			iter_1;
	size_t			iter_2;
}					t_buffer;

typedef struct s_request
{
	char			**separated;
	char			**line_with_substitutions;
	size_t			number;
}					t_request;

typedef struct s_redirect
{
	char			*name;
	int				output_flag;
	int				fd;

}					t_redirect;

typedef struct s_command
{
	char			*name;
	char			**args;
	t_redirect		*files;
}					t_command;

typedef struct s_fd
{
	int				pipe_flag;
	int				standard_output;
	int				standard_input;
	size_t			number_of_pipes;
	int				**pipeline;
}					t_fd;

typedef struct s_iter
{
	size_t			i;
	size_t			j;
	size_t			k;
	size_t			n;
}					t_iter;

typedef struct s_all
{
	t_env			*env;
	t_buffer		buffer;
	t_request		requests;
	t_command		*command;
	t_fd			fd;
	char			**separated_request;
	t_iter			iter;
	size_t			n;
	pid_t			*pid;
	int				status;
}					t_all;

int					error_while_binary_execution(t_all *all, size_t j);
void				execve_call(t_all *all, size_t j);
int					multiple_command_execution(t_all *all);

/*
** ########################################################################
** ############################# BUILTINS #################################
** ########################################################################
** ######################### Folder: builtins #############################
** ########################################################################
*/

/*
** File: pwd.c
*/

int					pwd(t_all *all);

/*
** File: env.c
*/

int					env(t_all *all, size_t j);

/*
** File: cd.c && cd_utils.c
*/

int					cd(t_all *all, size_t j);
int					cd_from_current_directory(t_all *all, size_t j);

/*
** File: echo.c
*/

int					echo(t_all *all, size_t j);

/*
** File: export.c
*/

int					export(t_all *all, size_t j);

/*
** File: exit.c
*/

int					exit_bash(t_all *all, size_t j);

/*
** File: unset.c
*/

int					unset(t_all *all, size_t j);

/*
** File: env_export_utils.c
*/

void				add_environment(t_all *all, char *name, char *value);
void				delete_environment(t_all *all, char *name);
char				**env_for_execve(t_all *all);
char				*look_for_env(t_all*all, char *name);

/*
** ########################################################################
** ########## IMPORTANT FUNCTIONS ON WHICH ALL PROGRAM IS BASED ###########
** ########################################################################
** ######################### Folder: important ############################
** ########################################################################
*/

/*
** File: execution.c
*/

void				execve_call(t_all *all, size_t j);
int					single_command_execution(t_all *all, size_t j);

/*
** File: parsing_and_execution.c
*/

int					parsing_and_execution(t_all *all);

/*
** File: pregame_ritual.c
*/

void				pregame_ritual(t_all *all, int ac, char **av, char **env);

/*
** File: redirects.c
*/

int					find_right_redirect_pipe(t_all *all, size_t j);
int					find_left_redirect_pipe(t_all *all, size_t j);
int					check_left_redirect_pipe(t_all *all);

/*
** File: signal_handling.c
*/

void				signal_ctrl_backslash(int sig);
void				signal_ctrl_c(int signal);

/*
** ########################################################################
** ############ FUNCTIONS WHERE ALL CYCLES OF PARSING HAPPENS #############
** ########################################################################
** ########################## Folder: parsing #############################
** ########################################################################
*/

/*
** File: filling_command_structure.c
*/

void				allocate_memory_for_commands(t_all *all);
int					filling_command_structure(t_all *all);

/*
** File: first_circle_of_parsing.c
*/

void				first_circle_of_parsing(t_all *all, size_t i);

/*
** File: memory_cleaning.c
*/

void				free_after_parsing(t_all *all);
void				clean_after_yourself(t_all *all, size_t i);
void				free_memory_in_case_of_invalid_request(t_all *all);

/*
** File: second_circle_of_parsing.c
*/

int					second_circle_of_parsing(t_all *all, size_t i);
/*
** File: request_separation.c
*/

void				separate_requests(t_all *all);
void				count_requests(t_all *all);

/*
** File: validation.c
*/

int					validation_of_requests(t_all *all);

/*
** ########################################################################
** ######################### Useful functions #############################
** ########################################################################
** ########################## Folder: utils ###############################
** ########################################################################
*/

size_t				ft_strlen(char *string);
void				*ft_realloc(void *ptr, size_t len);
char				**split(char *s, char c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(char *s1);
int					ft_strcmp(char *line1, char *line2);
int					get_next_line(int fd, char **line);
void				ft_strcpy(char *dst, char *src);
int					is_shielded(t_all *all);
int					is_special_symbol(char c);
void				ft_putchar_fd(char c, int fd);
int					ft_putendl_fd(char *s, int fd);
int					export_validation(t_all *all, char *name, size_t j);
void				ft_putstr_fd(char *s, int fd);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				*ft_bzero(void *b, size_t len);
void				str_to_lowercase(t_all *all, size_t j);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					change_exitcode_and_err_msg(t_all *all,
						char *msg, char *code, size_t j);
int					err_msg_with_no_command_name(t_all *all,
						 char *msg, char *code);
int					change_exitcode_and_errno(t_all *all, char *code, size_t j);
void				change_exitcode_success(t_all *all);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*strjoin_for_path(char const *s1, char const *s2);
void				skip_spaces(t_all *all);
void				stop_buffering(t_all *all);
int					stop_buffering_condition(t_all *all);
void				iterators_to_zero(t_all *all);
int					ft_isalpha(int c);
int					ft_atoi(char *str);
int					ft_isdigit(int c);
char				*ft_itoa(int n);
void				build_pipeline(t_all *all);
void				close_all_pipes(t_all *all);
int					requests_validation_after_first_circle(t_all *all,
						size_t i);
int					free_after_filling(t_all *all);

#endif
