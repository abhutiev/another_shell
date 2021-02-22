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

int		builtin_execution(t_all *all, size_t j)
{
	str_to_lowercase(all, j);
	if (ft_strcmp("cd", all->command[j].name) == 0)
		return (cd(all, j));
	else if (ft_strcmp("echo", all->command[j].name) == 0)
		return (echo(all, j));
	else if (ft_strcmp("env", all->command[j].name) == 0)
		return (env(all, j));
	else if (ft_strcmp("exit", all->command[j].name) == 0)
		return (exit_bash(all, j));
	else if (ft_strcmp("export", all->command[j].name) == 0)
		return (export(all, j));
	else if (ft_strcmp("pwd", all->command[j].name) == 0)
		return (pwd(all));
	else if (ft_strcmp("unset", all->command[j].name) == 0)
		return (unset(all, j));
	else
		return (0);
}

int 	error_while_binary_executing(t_all *all, size_t j)
{
	if (look_for_env(all, "PATH"))
		change_exitcode_and_err_msg(all, CMD_NOT_FOUND, "127", j);
	else
		change_exitcode_and_err_msg(all, NO_FILE_OR_DIRECTORY, "127", j);
	return (127);
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
		execve(all->command[j].name, all->command[j].args, env_for_execve(all));
		ways = split(look_for_env(all, "PATH"), ':');
		if (ways)
		{
			while (ways[i])
				execve(strjoin_for_path(ways[i++], all->command[j].name), all->command[j].args, env_for_execve(all));
		}
		error_while_binary_executing(all, j);
		printf("1\n");
		exit(1);
	}
	wait(0);
}

int		one_command_execution(t_all * all)
{
	return (1);
}

void	request_execution(t_all *all)
{
	size_t	j;

	j = 0;
	if (all->command[0].output_flag == STANDART_OUTPUT)

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
