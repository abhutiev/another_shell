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
	close_file_descriptors(all);
	return (0);
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

void	close_all_pipes(t_all *all)
{
    size_t	j;

    j = 0;
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

void	wait_all(t_all *all)
{
	size_t j = 0;

//	dup2(all->fd.standard_output, 1);
//	dup2(all->fd.standard_input, 0);
	while (all->pid[j])
	{
		waitpid(all->pid[j], NULL, WUNTRACED);
//		if (all->command[j + 1].name != NULL)
//			printf("%d\n", close(all->fd.pipeline[j][1]));
		if (!j)
		{
			close(0);
			printf("%d\n", close(all->fd.pipeline[j][0]));
			printf("%d\n", close(all->fd.pipeline[j][1]));
		}
		else if (all->command[j + 1].name != NULL)
		{
			printf("%d\n", close(all->fd.pipeline[j][1]));
		}
		j++;
	}
	free(all->pid);
}

int		multiple_command_execution(t_all *all)
{
	size_t	j;

	j = 0;
    build_pipeline(all);
	while (all->command[j].name)
	{
		fork_work(all, j);
		j++;
	}

	j = 0;
	while (all->pid[j]) {
        if (j == 0)
        {
            close(all->fd.pipeline[j][1]);
        }
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
    free(all->pid);
    close_all_pipes(all);
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
		ft_putstr_fd(SHELL_NAME, 1);
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
