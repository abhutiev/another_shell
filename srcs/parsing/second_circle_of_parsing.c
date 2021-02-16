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

static void	get_arg_from_single_quotes(t_all *all, size_t n)
{
	all->buffer.iter_2 = 0;
	all->buffer.iter_1++;
	all->buffer.line_2 = (char *)malloc(1000);
	while (all->buffer.line_1[all->buffer.iter_1] && all->buffer.line_1[all->buffer.iter_1] != '\'')
		all->buffer.line_2[all->buffer.iter_2++] = all->buffer.line_1[all->buffer.iter_1++];
	all->buffer.line_2[all->buffer.iter_2] = '\0';
	all->separated_request[n] = all->buffer.line_2;
}

static void	get_arg_from_double_quotes(t_all *all, size_t n)
{
	all->buffer.iter_2 = 0;
	all->buffer.line_2 = (char *)malloc(1000);
	all->buffer.iter_1++;
	while (all->buffer.line_1[all->buffer.iter_1] && all->buffer.line_1[all->buffer.iter_1] != '\"')
	{
		if (all->buffer.line_1[all->buffer.iter_1] == '\\')
		{
			all->buffer.iter_1++;
			if (all->buffer.line_1[all->buffer.iter_1])
				all->buffer.line_2[all->buffer.iter_2++] = all->buffer.line_1[all->buffer.iter_1++];
		}
		else
			all->buffer.line_2[all->buffer.iter_2++] = all->buffer.line_1[all->buffer.iter_1++];
	}
	all->buffer.line_2[all->buffer.iter_2] = '\0';
	all->separated_request[n] = all->buffer.line_2;
}

static void	get_arg_after_backslash(t_all *all, size_t n)
{
	all->buffer.iter_1++;
	all->buffer.line_2[0] = all->buffer.line_1[all->buffer.iter_1++];
	all->buffer.iter_2 = 1;
	all->buffer.line_2 = (char *)malloc(1000);
	while (all->buffer.line_1[all->buffer.iter_1] && all->buffer.line_1[all->buffer.iter_1] != ' ' && all->buffer.line_1[all->buffer.iter_1] != ';')
	{
		if (all->buffer.line_1[all->buffer.iter_1] == '\\')
		{
			all->buffer.iter_1++;
			if (all->buffer.line_1[all->buffer.iter_1])
				all->buffer.line_2[all->buffer.iter_2++] = all->buffer.line_1[all->buffer.iter_1++];
		}
		else
			all->buffer.line_2[all->buffer.iter_2++] = all->buffer.line_1[all->buffer.iter_1++];
	}
	all->buffer.line_2[all->buffer.iter_2] = '\0';
	all->separated_request[n] = all->buffer.line_2;
}

static void	get_arg_ordinary(t_all *all, size_t n)
{
	all->buffer.iter_2 = 0;
	all->buffer.line_2 = (char *)malloc(1000);
	while (all->buffer.line_1[all->buffer.iter_1] && all->buffer.line_1[all->buffer.iter_1] != ' ' && all->buffer.line_1[all->buffer.iter_1] != ';')
	{
		if (all->buffer.line_1[all->buffer.iter_1] == '\\')
		{
			all->buffer.iter_1++;
			if (all->buffer.line_1[all->buffer.iter_1])
				all->buffer.line_2[all->buffer.iter_2++] = all->buffer.line_1[all->buffer.iter_1++];
		}
		else
			all->buffer.line_2[all->buffer.iter_2++] = all->buffer.line_1[all->buffer.iter_1++];
	}
	all->buffer.line_2[all->buffer.iter_2] = '\0';
	all->separated_request[n] = all->buffer.line_2;
}

void		second_circle_of_parsing(t_all *all, size_t i)
{
	size_t		n;

	all->buffer.iter_1 = 0;
	all->buffer.line_1 = all->requests.line_with_substitutions[i];
	all->separated_request = (char **)malloc(1024);
	n = 0;
	while (all->buffer.line_1[all->buffer.iter_1] && all->buffer.line_1[all->buffer.iter_1] != ';')
	{
		if (all->buffer.line_1[all->buffer.iter_1] == ' ')
		{
			all->buffer.iter_1++;
			continue;
		}
		else if (all->buffer.line_1[all->buffer.iter_1] == '\'')
			get_arg_from_single_quotes(all, n++);
		else if (all->buffer.line_1[all->buffer.iter_1] == '\"')
			get_arg_from_double_quotes(all, n++);
		else if (all->buffer.line_1[all->buffer.iter_1] == '\\')
			get_arg_after_backslash(all, n++);
		else
			get_arg_ordinary(all, n++);
		all->buffer.iter_1++;
	}
	free(all->requests.line_with_substitutions[i]);
	i = 0;
	all->separated_request[n] = NULL;
	while (all->separated_request[i])
	{
		//printf("%s\n", all->separated_request[i]);
		i++;
	}
}
