/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:22:59 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/28 15:23:01 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_pipes(t_all *all)
{
	size_t	j;

	j = 0;
	free(all->pid);
	dup2(all->fd.standard_output, 1);
	dup2(all->fd.standard_input, 0);
	while (j < all->fd.number_of_pipes)
	{
		close(all->fd.pipeline[j][0]);
		close(all->fd.pipeline[j][1]);
		free(all->fd.pipeline[j]);
		j++;
	}
	free(all->fd.pipeline);
}

void	build_pipeline(t_all *all)
{
	size_t	j;
	all->fd.number_of_pipes = 0;
	while (all->command[all->fd.number_of_pipes].name)
		all->fd.number_of_pipes++;
	all->pid = (pid_t *)ft_calloc(all->fd.number_of_pipes + 1, sizeof(pid_t));
	all->fd.pipeline = ft_calloc(all->fd.number_of_pipes--, sizeof(int) * 2);
	j = 0;
	while (j < all->fd.number_of_pipes)
	{
		all->fd.pipeline[j] = ft_calloc(2, sizeof(int));
		pipe(all->fd.pipeline[j]);
		j++;
	}
}

int		find_left_redirect_pipe(t_all *all)
{
	size_t	i;
	int		current_fd;

	i = 0;
	current_fd = 0;
	while (all->command[0].files[i].name)
	{
		if (all->command[0].files[i].output_flag == TO_LEFT_REDIR)
		{
			if (current_fd != 0)
				close(current_fd);
			current_fd = open(all->command[0].files[i].name, O_RDONLY);
			if (current_fd == -1)
			{
				change_exitcode_and_err_msg(all, NO_FILE_OR_DIR, "1", 0);
				return (-1);
			}
		}
		i++;
	}
	return (current_fd);
}

int		multiple_command_execution(t_all *all)
{
	size_t	j;
	int		input_fd;

	j = 0;
	input_fd = find_left_redirect_pipe(all);
	if (input_fd == -1)
		return (1);
	else if (input_fd)
		dup2(input_fd, 0);
	build_pipeline(all);
	while (all->command[j].name)
		fork_work(all, j++);
	j = 0;
	while (all->pid[j]) {
		if (j == 0)
			close(all->fd.pipeline[j][1]);
		else if (all->command[j + 1].name != NULL)
		{
			waitpid(all->pid[j - 1], NULL, WUNTRACED);
			close(all->fd.pipeline[j - 1][0]);
			waitpid(all->pid[j], NULL, WUNTRACED);
			close(all->fd.pipeline[j][1]);
		}
		else if (all->command[j + 1].name == NULL)
		{
			close(all->fd.pipeline[j - 1][1]);
			waitpid(all->pid[j], NULL, WUNTRACED);
			close(all->fd.pipeline[j - 1][0]);
		}
		j++;
	}
	wait(0);
	close_all_pipes(all);
	return (0);
}

int 	single_command_execution(t_all *all, size_t j)
{
	if (!open_file_descriptors(all, j))
	{
		if (!builtin_execution(all, j))
			binary_execution(all, j);
	}
	else
		return (1);
	close_file_descriptors(all);
	return (0);
}

int 	request_execution(t_all *all)
{
	if (!all->fd.pipe_flag)
		return (single_command_execution(all, 0));
	return (multiple_command_execution(all));
}
