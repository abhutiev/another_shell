/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_separation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 21:42:43 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/05 21:42:44 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		count_requests(t_all *all)
{
	all->buffer.iter_1 = 0;
	all->requests.number = 1;
	while (all->buffer.line_1[all->buffer.iter_1])
	{
		if (all->buffer.line_1[all->buffer.iter_1] == ';' && !is_shielded(all))
			all->requests.number++;
		else if (all->buffer.line_1[all->buffer.iter_1] == '\'' &&
														!is_shielded(all))
		{
			all->buffer.iter_1++;
			while (all->buffer.line_1[all->buffer.iter_1] &&
							all->buffer.line_1[all->buffer.iter_1] != '\'')
				all->buffer.iter_1++;
		}
		else if (all->buffer.line_1[all->buffer.iter_1] == '\"'
														&& !is_shielded(all))
		{
			all->buffer.iter_1++;
			while (all->buffer.line_1[all->buffer.iter_1] &&
							all->buffer.line_1[all->buffer.iter_1] != '\"')
				all->buffer.iter_1++;
		}
		all->buffer.iter_1++;
	}
}

static void	prepare_for_separation(t_all *all)
{
	all->iter.i = 0;
	all->requests.separated =
			(char **)ft_calloc(all->requests.number + 1, sizeof(char *));
	all->requests.line_with_substitutions =
			(char **)ft_calloc(all->requests.number + 1, sizeof(char *));
	all->buffer.iter_1 = 0;
	all->requests.number = 0;
}

static void	grep_till_semicolon(t_all *all)
{
	all->requests.separated[all->requests.number] =
			ft_substr(all->buffer.line_1, all->iter.i,
		all->buffer.iter_1 - all->iter.i);
	all->iter.i = all->buffer.iter_1 + 1;
	all->requests.number++;
}

static void	grep_till_single_quote(t_all *all)
{
	all->buffer.iter_1++;
	while (all->buffer.line_1[all->buffer.iter_1] &&
				all->buffer.line_1[all->buffer.iter_1] != '\'')
		all->buffer.iter_1++;
}

void		separate_requests(t_all *all)
{
	prepare_for_separation(all);
	while (all->buffer.line_1[all->buffer.iter_1])
	{
		if (all->buffer.line_1[all->buffer.iter_1] == ';' && !is_shielded(all))
			grep_till_semicolon(all);
		else if (all->buffer.line_1[all->buffer.iter_1] == '\''
		&& !is_shielded(all))
			grep_till_single_quote(all);
		else if (all->buffer.line_1[all->buffer.iter_1] == '\"' &&
		!is_shielded(all))
		{
			all->buffer.iter_1++;
			while (all->buffer.line_1[all->buffer.iter_1] &&
							all->buffer.line_1[all->buffer.iter_1] != '\"')
				all->buffer.iter_1++;
		}
		all->buffer.iter_1++;
	}
	all->requests.separated[all->requests.number] =
	ft_substr(all->buffer.line_1, all->iter.i, all->buffer.iter_1
														- all->iter.i + 1);
	free(all->buffer.line_1);
}
