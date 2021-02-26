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

int 	single_command_execution(t_all *all, size_t j)
{
	if (!open_file_descriptors(all, j))
	{
		if (!builtin_execution(all, j))
			binary_execution(all, j);
	}
	else
		return (1);
	close_file_descriptors(all, j);
	return (0);
}

void	build_pipeline(t_all *all)
{
	size_t	j;
	all->fd.number_of_pipes = 0;
	while (all->command[all->fd.number_of_pipes].name)
		all->fd.number_of_pipes++;
	all->fd.pipeline = ft_calloc(all->fd.number_of_pipes--, sizeof(int) * 2);
	j = 0;
	while (j <= all->fd.number_of_pipes)
	{
		all->fd.pipeline[j] = ft_calloc(2, sizeof(int));
		pipe(all->fd.pipeline[j]);
		j++;
	}
}

void	close_all_pipes(t_all *all)
{
	size_t	j;

	j = 0;
	while (j <= all->fd.number_of_pipes)
	{
		close(all->fd.pipeline[j][0]);
		close(all->fd.pipeline[j][1]);
		free(all->fd.pipeline[j]);
		j++;
	}
	dup2(all->fd.standard_output, 1);
	dup2(all->fd.standard_input, 0);
	free(all->fd.pipeline);
}

int		multiple_command_execution(t_all *all)
{
	size_t	j;

	j = 0;
	build_pipeline(all);
	while (all->command[j].name)
	{
		if (!all->command[j + 1].name)
		{
			dup2(all->fd.standard_output, 1); // возвращаем дескриптор 1 на место
		}
		else
			dup2(all->fd.pipeline[j + 1][0], 1); // пиши в 0 пайп следующего вместо 1
		if (j != 0)
			dup2(all->fd.pipeline[j][1], 0); // читай из 1 пайп вместо 0
//		if (!open_file_descriptors(all, j))
		binary_execution(all, j);
//		close_file_descriptors(all, j);
		j++;
	}
	return (0);
}

int 	request_execution(t_all *all)
{

	if (!all->fd.pipe_flag)
		return (single_command_execution(all, 0));
	return (multiple_command_execution(all));
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
			free_memory_in_case_of_invalid_request(&all);
			continue ;
		}
		parsing_and_execution(&all);
	}
	return (0);
}
