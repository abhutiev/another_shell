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

#include "includes/minishell.h"



void	request_execution(t_all *all)
{
	
	j = 0;
	while (all->command[j].name)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(to_usr_bin(all->command[j].name), all->command[j].args, all->envi);
			exit(0);
		}
		wait(0);
		j++;
	}
}

void	parsing_and_execution(t_all *all)
{
	size_t	i;


	i = 0;
	while (all->requests.separated[i])
	{
		first_circle_of_parsing(all, i);
		second_circle_of_parsing(all, i);
		allocate_memory_for_commands(all);
		filling_command_structure(all);

		free_command_names(all);
		i++;
	}
	clean_after_yourself(all, i);
}

int		main(int argc, char **argv, char **en)
{
	t_all	all;

	all.envi = en;
	pregame_ritual(&all, argc, argv, en);
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
