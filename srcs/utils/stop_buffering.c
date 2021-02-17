/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_buffering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:53:22 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/17 17:53:23 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		stop_buffering_condition(t_all *all)
{
	if ((all->buffer.line_1[all->buffer.iter_1] == ' ' ||
		all->buffer.line_1[all->buffer.iter_1] == '>' ||
		all->buffer.line_1[all->buffer.iter_1] == '|' ||
		all->buffer.line_1[all->buffer.iter_1] == '<') && !is_shielded(all))
		return (1);
	else
		return (0);
}

void	stop_buffering(t_all *all)
{
	all->buffer.line_2[all->buffer.iter_2] = '\0';
	all->buffer.iter_2 = 0;
	all->separated_request[all->n++] = all->buffer.line_2;
	all->buffer.line_2 = (char *)ft_calloc(1024, 1);
	if (all->buffer.line_1[all->buffer.iter_1] == '>')
	{
		all->separated_request[all->n++] = ft_strdup(">");
		all->buffer.iter_1++;
	}
	else if (all->buffer.line_1[all->buffer.iter_1] == '<')
	{
		all->separated_request[all->n++] = ft_strdup("<");
		all->buffer.iter_1++;
	}
	else if (all->buffer.line_1[all->buffer.iter_1] == '|')
	{
		all->separated_request[all->n++] = ft_strdup("|");
		all->buffer.iter_1++;
	}
	else if (!ft_strncmp(all->buffer.line_1 + all->buffer.iter_1, ">>", 2))
	{
		all->separated_request[all->n++] = ft_strdup("|");
		all->buffer.iter_1 += 2;
	}
	skip_spaces(all);
}
