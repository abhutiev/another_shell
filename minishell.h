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
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>


# define SHELL_NAME "bash"

typedef struct		s_env
{
	char			*name;
	char			*value;
}					t_env;

typedef struct		s_all
{
	t_env			*env;

}					t_all;

size_t				ft_strlen(char *string);
char				**split(char *s, char c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(const char *s1);
int					ft_strcmp(char *line1, char *line2);

void				load_environments(t_all *all, char **env);
void				add_environment(t_all *all, char *name, char *value);
void				sort_environments(t_all *all);
void				delete_environment(t_all *all, char *name);
void				display_env(t_all *all);






size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				*ft_bzero(void *b, size_t len);



#endif
