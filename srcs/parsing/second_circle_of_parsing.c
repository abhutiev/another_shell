/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_circle_of_parsing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 05:25:23 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/10 05:25:24 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fill_buffer_from_single_quotes(t_all *all)
{
	all->buffer.iter_1++;
	while ((all->buffer.line_1[all->buffer.iter_1] != '\'' &&
	all->buffer.line_1[all->buffer.iter_1] != '>' &&
	all->buffer.line_1[all->buffer.iter_1] != '|' &&
	all->buffer.line_1[all->buffer.iter_1] != '<') && !is_shielded(all))
	{
		all->buffer.line_2[all->buffer.iter_2++] = all->buffer.line_1[all->buffer.iter_1++];
	}
	all->buffer.iter_1++;
}

static void	fill_buffer_from_double_quotes(t_all *all)
{
	all->buffer.iter_1++;
	while ((all->buffer.line_1[all->buffer.iter_1] != '\"' &&
	all->buffer.line_1[all->buffer.iter_1] != '>' &&
	all->buffer.line_1[all->buffer.iter_1] != '|' &&
	all->buffer.line_1[all->buffer.iter_1] != '<') && !is_shielded(all))
	{
		all->buffer.line_2[all->buffer.iter_2++] = all->buffer.line_1[all->buffer.iter_1++];
	}
	all->buffer.iter_1++;
}

void		skip_spaces(t_all *all)
{
	while (all->buffer.line_1[all->buffer.iter_1] == ' ')
		all->buffer.iter_1++;
}

int		stop_buffering(t_all *all)
{
	if ((all->buffer.line_1[all->buffer.iter_1] == ' ' ||
	all->buffer.line_1[all->buffer.iter_1] == '>' ||
	all->buffer.line_1[all->buffer.iter_1] == '|' ||
	all->buffer.line_1[all->buffer.iter_1] == '<') && !is_shielded(all))
		return (1);
	else
		return (0);
}

void		second_circle_of_parsing(t_all *all, size_t i)
{
	size_t		n;

	all->buffer.iter_1 = 0;
	skip_spaces(all);
	all->buffer.line_1 = all->requests.line_with_substitutions[i];
	all->buffer.iter_2 = 0;
	all->buffer.line_2 = (char *)ft_calloc(1024, 1);
	all->separated_request = (char **)ft_calloc(256, sizeof(char *));
	n = 0;
	while (all->buffer.line_1[all->buffer.iter_1] && all->buffer.line_1[all->buffer.iter_1] != ';')
	{
		if (stop_buffering(all))
		{
			all->buffer.line_2[all->buffer.iter_2] = '\0';
			all->buffer.iter_2 = 0;
			all->separated_request[n++] = all->buffer.line_2;
			all->buffer.line_2 = (char *)ft_calloc(1024, 1);
			if (all->buffer.line_1[all->buffer.iter_1] == '>')
			{
				all->separated_request[n++] = ft_strdup(">");
				all->buffer.iter_1++;
			}
			else if (all->buffer.line_1[all->buffer.iter_1] == '<')
			{
				all->separated_request[n++] = ft_strdup("<");
				all->buffer.iter_1++;
			}
			else if (all->buffer.line_1[all->buffer.iter_1] == '|')
			{
				all->separated_request[n++] = ft_strdup("|");
				all->buffer.iter_1++;
			}
			else if (!ft_strncmp(all->buffer.line_1 + all->buffer.iter_1, ">>", 2))
			{
				all->separated_request[n++] = ft_strdup("|");
				all->buffer.iter_1 += 2;
			}
			skip_spaces(all);
		}
		if (all->buffer.line_1[all->buffer.iter_1] == '\"')
			fill_buffer_from_double_quotes(all);
		else if (all->buffer.line_1[all->buffer.iter_1] == '\'')
			fill_buffer_from_single_quotes(all);
		else
		{
			if (all->buffer.line_1[all->buffer.iter_1] == '\\')
			{
				all->buffer.line_2[all->buffer.iter_2++] = all->buffer.line_1[++all->buffer.iter_1];
				all->buffer.iter_1++;
			}
			else
				all->buffer.line_2[all->buffer.iter_2++] = all->buffer.line_1[all->buffer.iter_1++];
		}

	}
	free(all->requests.line_with_substitutions[i]);
	all->buffer.line_2[all->buffer.iter_2] = '\0';
	all->buffer.iter_2 = 0;
	all->separated_request[n++] = all->buffer.line_2;
	all->separated_request[n] = NULL;
}
