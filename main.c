/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 03:41:25 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/04 03:41:27 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	second_circle_of_parsing(t_all *all, size_t i)
{
	// разбиваем реквесты поаргументно и потом удаляем \\

	all->buffer.iter_1 = 0;
	all->buffer.iter_2 = 0;
	all->buffer.line_1 = all->requests.line_with_substitutions;
	all->buffer.line_2 = (char *)ft_calloc(1000, sizeof(char));
	while (all->buffer.line_2[all->buffer.iter_2])
	{
		if (all->buffer.line_2[all->buffer.iter_2] == '\\')
		{

		}
		//else if
	}
	free(all->buffer.line_2);
}

void	parsing_and_execution(t_all *all)
{
	size_t	i;

	i = 0;
	while (all->requests.separated[i])
	{
		first_circle_of_parsing(all, i);
		//second_circle_of_parsing(all, i);
		printf("%s\n", all->requests.line_with_substitutions[i]);
		free(all->requests.line_with_substitutions[i]);
		i++;
	}
	free(all->requests.separated[i]);
	free(all->requests.separated);
	free(all->requests.line_with_substitutions[i]);
	free(all->requests.line_with_substitutions);
}

int		main(int argc, char **argv, char **env)
{
	t_all	all;

	pregame_ritual(&all, argc, argv, env);
	while (1)
	{
		write(1, SHELL_NAME, ft_strlen(SHELL_NAME));
		get_next_line(0, &(all.buffer.line_1));
		count_requests(&all);
		separate_requests(&all);
		parsing_and_execution(&all);
	}
	return (0);
}
