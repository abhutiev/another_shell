/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 03:50:41 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/04 03:50:44 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h> //
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# define SHELL_NAME 	"\033[0;34mbash:\033[1;34m"
# define PIPE			1
# define RIGHT_REDIR	2
# define D_RIGHT_REDIR	3
# define LEFT_REDIR		4

typedef struct		s_env
{
	char			*name;
	char			*value;
}					t_env;

typedef struct		s_buffer
{
	char			*line_1;
	char			*line_2;
	size_t			iter_1;
	size_t			iter_2;
}					t_buffer;

typedef struct		s_request
{
	char			**separated;
	char			**line_with_substitutions;
	size_t			number;
}					t_request;

typedef struct		s_command
{
	char			*name;
	char			**args;
	size_t			*number_of_args;
	size_t			number_of_commands;
}					t_command;

typedef struct		s_fd
{
	int				standard_output;
	int				standard_input;
	int				*pipeline[2];
}					t_fd;
typedef struct		s_all
{
	t_env			*env;
	t_buffer 		buffer;
	t_request		requests;
	t_command		*command;
	t_fd			fd;
	char			**separated_request;
}					t_all;


void				first_circle_of_parsing(t_all *all, size_t i);
void				second_circle_of_parsing(t_all *all, size_t i);

void				pregame_ritual(t_all *all, int ac, char **av, char **env);

void				separate_requests(t_all *all);
void				count_requests(t_all *all);






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

void				pwd(t_all *all);

/*
** File: env.c
*/

void				env(t_all *all);

/*
** File: cd.c
*/


/*
** File: echo.c
*/

/*
** File: export.c
*/

/*
** File: exit.c
*/

/*
** File: unset.c
*/

/*
** File: work_with_environments.c
*/

void				load_environments(t_all *all, char **env);
void				add_environment(t_all *all, char *name, char *value);
void				sort_environments(t_all *all);
void				delete_environment(t_all *all, char *name);
void				display_env(t_all *all);

/*
** ########################################################################
** ######################### Useful functions #############################
** ########################################################################
** ########################## Folder: utils ###############################
** ########################################################################
*/

/*
** File: strlen.c
*/

size_t				ft_strlen(char *string);

/*
** File: split.c
*/

char				**split(char *s, char c);

/*
** File: calloc.c
*/

void				*ft_calloc(size_t count, size_t size);

/*
** File: substr.c
*/

char				*ft_substr(char const *s, unsigned int start, size_t len);

/*
** File: strdup.c
*/

char				*ft_strdup(const char *s1);

/*
** File: strcmp.c
*/

int					ft_strcmp(char *line1, char *line2);

/*
** File: gnl.c
*/

int					get_next_line(int fd, char **line);

/*
** File: strcpy.c
*/

void				ft_strcpy(char *dst, char *src);

/*
** File: is_shielded.c
*/

int					is_shielded(t_all *all);

/*
** File: is_special_symbol.c
*/

int					is_special_symbol(char c);

/*
** File: putchar.c
*/

void				ft_putchar_fd(char c, int fd);

/*
** File: putendl.c
*/

void				ft_putendl_fd(char *s, int fd);

/*
** File: putstr.c
*/

void				ft_putstr_fd(char *s, int fd);

/*
** File: strlcpy.c
*/

size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);

/*
** File: bzero.c
*/

void				*ft_bzero(void *b, size_t len);

#endif
