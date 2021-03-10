#include "../../includes/minishell.h"

static int	builtin_execution(t_all *all, size_t j)
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

void	execve_call(t_all *all, size_t j)
{
	size_t	i;
	char	**ways;

	execve(all->command[j].name, all->command[j].args,
		env_for_execve(all));
	ways = split(look_for_env(all, "PATH"), ':');
	i = 0;
	if (ways)
	{
		while (ways[i])
			execve(strjoin_for_path(ways[i++],
				all->command[j].name),
					all->command[j].args, env_for_execve(all));
	}
	error_while_binary_execution(all, j);
	exit(127);
}

static void	binary_exec_no_pipe(t_all *all)
{
	pid_t	pid;
	char	*tmp;

	g_signal_mode = 0;
	pid = fork();
	if (pid == 0)
		execve_call(all, 0);
	wait(&(all->status));
	delete_environment(all, "?");
	tmp = ft_itoa(all->status / 255);
	add_environment(all, "?", tmp);
	free(tmp);
}

int	single_command_execution(t_all *all, size_t j)
{
	int		fd_in;
	int		fd_out;

	if (check_left_redirect_pipe(all))
		return (1);
	fd_in = find_left_redirect_pipe(all, 0);
	fd_out = find_right_redirect_pipe(all, 0);
	if (fd_in)
		dup2(fd_in, 0);
	if (fd_out)
		dup2(fd_out, 1);
	if (!builtin_execution(all, j))
		binary_exec_no_pipe(all);
	if (fd_in)
		close(fd_in);
	if (fd_out)
		close(fd_out);
	dup2(all->fd.standard_output, 1);
	dup2(all->fd.standard_input, 0);
	return (0);
}
