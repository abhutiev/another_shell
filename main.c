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

int8_t	is_pipe_or_request()
{

}

void	free_separated_request(t_all *all)
{
	size_t	i;

	i = 0;
	while (all->separated_request[i])
	{
		printf("%s\n", all->separated_request[i]);
		free(all->separated_request[i++]);
	}
	free(all->separated_request[i]);
	free(all->separated_request);
}

void	allocate_memory_for_commands(t_all *all)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (all->separated_request[i])
	{
		if (!ft_strcmp(all->separated_request[i], ">") ||
				!ft_strcmp(all->separated_request[i], ">>") ||
					!ft_strcmp(all->separated_request[i], "<") ||
						!ft_strcmp(all->separated_request[i], "|"))
			counter++;
		i++;
	}
	all->command = (t_command *)ft_calloc(sizeof(t_command) * (counter + 2));
}

void	filling_command_structure(t_all *all)
{

}

void	parsing_and_execution(t_all *all)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (all->requests.separated[i])
	{
		first_circle_of_parsing(all, i);
		second_circle_of_parsing(all, i);
		//count
		allocate_memory_for_commands(all);
		filling_command_structure(all);
		free_separated_request(all);
		i++;
	}
	free(all->requests.separated[i]);
	free(all->requests.separated);
	free(all->requests.line_with_substitutions[i]);
	free(all->requests.line_with_substitutions);
}

int		main(int argc, char **argv, char **en)
{
	t_all	all;

	pregame_ritual(&all, argc, argv, en);
	free(NULL);
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
