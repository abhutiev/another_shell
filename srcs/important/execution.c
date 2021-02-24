/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 22:57:17 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/24 22:57:18 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			builtin_execution(t_all *all, size_t j)
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

static int	error_while_binary_execution(t_all *all, size_t j)
{
	if (look_for_env(all, "PATH"))
		change_exitcode_and_err_msg(all, CMD_NOT_FOUND, "127", j);
	else
		change_exitcode_and_err_msg(all, NO_FILE_OR_DIR, "127", j);
	return (127);
}

void		binary_execution(t_all *all, size_t j)
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
			while (ways[i])
				execve(strjoin_for_path(ways[i++],
						all->command[j].name), all->command[j].args,
													env_for_execve(all));
		error_while_binary_execution(all, j);
		exit(1);
	}
	wait(0);
}
