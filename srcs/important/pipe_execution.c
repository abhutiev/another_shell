#include "../../includes/minishell.h"

static void	close_excess_fd(t_all *all, size_t fd_in, size_t fd_out)
{
	size_t	j;

	j = 0;
	while (j < all->fd.number_of_pipes)
	{
		if (j != fd_in && all->fd.pipeline[j][0])
			close(all->fd.pipeline[j][0]);
		if (j != fd_out && all->fd.pipeline[j][1])
			close(all->fd.pipeline[j][1]);
		j++;
	}
}

static void	binary_exec_in_pipe(t_all *all, size_t j, int out_fd, int in_fd)
{
	all->pid[j] = fork();
	if (all->pid[j] == 0)
	{
		if (j == 0)
		{
			dup2(all->fd.pipeline[j][1], 1);
			close_excess_fd(all, 10000, j);
		}
		else if (all->command[j + 1].name != NULL)
		{
			dup2(all->fd.pipeline[j - 1][0], 0);
			dup2(all->fd.pipeline[j][1], 1);
			close_excess_fd(all, (j - 1), j);
		}
		else if (all->command[j + 1].name == NULL)
		{
			dup2(all->fd.pipeline[j - 1][0], 0);
			close_excess_fd(all, (j - 1), 10000);
		}
		if (in_fd)
			dup2(in_fd, 0);
		if (out_fd)
			dup2(out_fd, 1);
		execve_call(all, j);
	}
}

static void	wait_processes_close_fd(t_all *all)
{
	size_t	j;

	j = 0;
	while (all->pid[j])
	{
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
}

int	multiple_command_execution(t_all *all)
{
	size_t	j;
	int		input_fd;
	int		output_fd;

	j = 0;
	if (check_left_redirect_pipe(all))
		return (1);
	build_pipeline(all);
	while (all->command[j].name)
	{
		output_fd = find_right_redirect_pipe(all, j);
		input_fd = find_left_redirect_pipe(all, j);
		g_signal_mode = 0;
		binary_exec_in_pipe(all, j++, output_fd, input_fd);
	}
	wait_processes_close_fd(all);
	return (0);
}
