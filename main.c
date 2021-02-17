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

int		builtin_execution(t_all *all, size_t j)
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
//	else if (!ft_strcmp("unset", all->command[j].name))
//		return (1);
	else
		return (0);
}

void	binary_execution(t_all *all, size_t j)
{
	pid_t	pid;
	char	**ways;
	size_t	i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		ways = split(look_for_env(all, "PATH"), ':');
		while (ways[i])
		{
			execve(strjoin_for_bin(ways[i], all->command[j].name), all->command[j].args, env_for_execve(all));
			i++;
		}
		ft_putstr_fd(SHELL_NAME, 1);
		ft_putstr_fd(all->command[j].name, 1);
		ft_putendl_fd(": No such file or directory", 1);
		exit(0);
	}
	wait(0);
}

void	request_execution(t_all *all)
{
	size_t	j;

	j = 0;
	while (all->command[j].name)
	{
		if (builtin_execution(all, j))
		{
			j++;
			continue ;
		}
		binary_execution(all, j);
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
