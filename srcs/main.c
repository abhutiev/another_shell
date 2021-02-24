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

#include "../includes/minishell.h"

void	request_execution(t_all *all)
{
	size_t j;

	j = 0;
	while (all->command[j].name)
	{
		if (open_file_descriptors(all, j))
		{
			close_file_descriptors(all, j);
			j++;
			continue ;
		}
		if (!builtin_execution(all, j))
			binary_execution(all, j);
		close_file_descriptors(all, j);
		j++;
	}
}

int		main(int argc, char **argv, char **en)
{
	t_all	all;

	pregame_ritual(&all, argc, argv, en);
	while (1)
	{
		write(1, SHELL_NAME, ft_strlen(SHELL_NAME));
		get_next_line(0, &(all.buffer.line_1));
		count_requests(&all);
		separate_requests(&all);
		if (validation_of_requests(&all))
		{
			free_requests_in_case_of_invalid_request(&all);
			continue ;
		}
		parsing_and_execution(&all);
	}
	return (0);
}
