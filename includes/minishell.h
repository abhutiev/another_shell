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

# define SHELL_NAME "\033[0;34mbash:\033[1;34m"

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
	size_t			number_of_args;
	size_t			number_of_commands;
}					t_command;

typedef struct		s_fd
{
	int				standard_output;
	int				standard_input;
}					t_fd;
typedef struct		s_all
{
	t_env			*env;
	t_buffer 		buffer;
	t_request		requests;
	t_command		command;
	t_fd			descriptors;
}					t_all;

size_t				ft_strlen(char *string);
char				**split(char *s, char c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(const char *s1);
int					ft_strcmp(char *line1, char *line2);
int					get_next_line(int fd, char **line);
void				ft_strcpy(char *dst, char *src);
int					is_shielded(t_all *all);
int					is_special_symbol(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putstr_fd(char *s, int fd);





void				load_environments(t_all *all, char **env);
void				add_environment(t_all *all, char *name, char *value);
void				sort_environments(t_all *all);
void				delete_environment(t_all *all, char *name);
void				display_env(t_all *all);

void		first_circle_of_parsing(t_all *all, size_t i);
void				pregame_ritual(t_all *all, int ac, char **av, char **env);

void	separate_requests(t_all *all);
void	count_requests(t_all *all);


size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				*ft_bzero(void *b, size_t len);

#endif
