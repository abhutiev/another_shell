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

int		builtin_executed(t_all *all, size_t j)
{
	str_to_lowercase(all, j);
	if (!ft_strcmp("cd", all->command[j].name))
		return (1);
	else if (!ft_strcmp("echo", all->command[j].name))
		return (echo(all, j));
	else if (!ft_strcmp("env", all->command[j].name))
		return (env(all, j));
	else if (!ft_strcmp("exit", all->command[j].name))
		return (1);
	else if (!ft_strcmp("export", all->command[j].name))
		return (export(all, j));
	else if (!ft_strcmp("pwd", all->command[j].name))
		return (pwd(all));
	else if (!ft_strcmp("unset", all->command[j].name))
		return (1);
	else
		return (0);
}

void	request_execution(t_all *all)
{
	size_t	j;
	pid_t	pid;

	j = 0;
	while (all->command[j].name)
	{
		if (builtin_executed(all, j))
		{
			j++;
			continue ;
		}
		pid = fork();
		if (pid == 0)
		{
			execve((all->command[j].name), all->command[j].args, env_for_execve(all));
			execve(to_usr_bin(all->command[j].name), all->command[j].args, env_for_execve(all));
			execve(to_usr_local_bin(all->command[j].name), all->command[j].args, env_for_execve(all));
			execve(to_local_munki(all->command[j].name), all->command[j].args, env_for_execve(all));
			execve(to_usr_sbin(all->command[j].name), all->command[j].args, env_for_execve(all));
			execve(to_bin(all->command[j].name), all->command[j].args, env_for_execve(all));
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
		request_execution(all);
		free_command_names(all);
		i++;
	}
	clean_after_yourself(all, i);
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
		parsing_and_execution(&all);
	}
	return (0);
}
