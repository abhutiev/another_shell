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

typedef struct		s_all
{
	t_env			*env;
	t_buffer 		buffer;
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




void				load_environments(t_all *all, char **env);
void				add_environment(t_all *all, char *name, char *value);
void				sort_environments(t_all *all);
void				delete_environment(t_all *all, char *name);
void				display_env(t_all *all);

void				first_circle_of_parsing(t_all *all);


size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				*ft_bzero(void *b, size_t len);
void				flags_shutting_up(int argc, char **argv);

#endif
