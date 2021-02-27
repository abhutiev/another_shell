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
	char	**ways;
	size_t	i;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(all->command[j].name, all->command[j].args,
			   env_for_execve(all));
		ways = split(look_for_env(all, "PATH"), ':');
		i = 0;
		if (ways)
		{
			while (ways[i])
				execve(strjoin_for_path(ways[i++],
										all->command[j].name), all->command[j].args,
		   													env_for_execve(all));
		}
		error_while_binary_execution(all, j);
		exit(1);
	}
	wait(0);
}

void        close_some(size_t fd0, size_t fd1, t_all *all)
{
    size_t	j;

    j = 0;
    while (j < all->fd.number_of_pipes)
    {
        if (j != fd0 && all->fd.pipeline[j][0])
            close(all->fd.pipeline[j][0]);
        if (j != fd1 && all->fd.pipeline[j][1])
            close(all->fd.pipeline[j][1]);
        j++;
    }
}

void		fork_work(t_all *all, size_t j)
{
	char	**ways;
	size_t	i;

	all->pid[j] = fork();
	if (all->pid[j] == 0)
	{
        if (j == 0)
        {
            dup2(all->fd.pipeline[j][1], 1);
            close_some(10000, j, all);
        }
        else if (all->command[j + 1].name != NULL)
        {
            dup2(all->fd.pipeline[j - 1][0], 0);
            dup2(all->fd.pipeline[j][1], 1);
            close_some((j - 1), j, all);
        }
        else if (all->command[j + 1].name == NULL)
        {
            dup2(all->fd.pipeline[j - 1][0], 0);
            dup2(all->fd.standard_output, 1);
            close_some((j - 1), 10000, all);
        }
		execve(all->command[j].name, all->command[j].args, env_for_execve(all));
		ways = split(look_for_env(all, "PATH"), ':');
		i = 0;
		if (ways)
		{
			while (ways[i])
				execve(strjoin_for_path(ways[i++],
					all->command[j].name), all->command[j].args, env_for_execve(all));
		}
		error_while_binary_execution(all, j);
		exit(1);
	}
}
